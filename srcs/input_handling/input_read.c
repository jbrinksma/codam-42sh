/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_read.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:03:16 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/30 14:29:06 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>
#include <signal.h>

/*
**	Every time we return from input_read, we want to make sure that the content
**	in the vshdata struct which is related to the current readloop and command
**	line is cleared and/or reset or prepared for the next line.
*/

static int	reset_input_read_return(t_vshdata *data, int ret)
{
	data->input->c = '\0';
	data->line->index = 0;
	data->line->len_max = 64;
	data->line->len_cur = 0;
	if (ret == 0)
		data->curs->coords.y = input_get_curs_row();
	data->curs->cur_relative_y = 1;
	data->history->current = NULL;
	signal(SIGWINCH, SIG_DFL);
	if (ret == 0)
		resize_window_check(SIGWINCH);
	return (ret);
}

/*
**	First we check for the `signals`, of our input. If it is not one of those,
**	we check if it is a '\e' character, which might indicate the start of a
**	recognised ANSI escape sequence. If that is not the case, we will see
**	if the character indicates something special like cursor movement. And
**	Finally if that is not the case either, we will attempt to add the
**	byte into our command line.
**
**	@return NEW_PROMPT
**					This will be returned when a ctrl+c character is read
**					('\3'). It lets the shell know that the current line
**					is cancelled.
**
**	@return IR_EOF	This stands for "Input Read End Of File". It will occur
**					when we read a ctrl+d ('\4') character, and the current
**					line is empty, and the current prompt is not our main
**					prompt (think of a `dquote >` for example). The reason
**					IR_EOF is not returned if we are reading with our main
**					prompt is that `builtin_exit` will have been called
**					from within `input_parse_ctrl_d`, and thus the shell
**					will have exited.
**					(See `input_parse_ctrl_d` for more info.)
**
**	@return FUNCT_SUCCESS
**					This will be returned when a byte is succesfully read.
**
**	@return FUNCT_ERROR
**					This will be returned when an error occured during any stage
**					of parsing the byte (e.g. allocation error).
*/

static int	input_parse(t_vshdata *data)
{
	int		ret;

	if (input_parse_ctrl_c(data) == FUNCT_SUCCESS)
		return (reset_input_read_return(data, NEW_PROMPT));
	ret = input_parse_ctrl_d(data);
	if (ret == IR_EOF)
		return (IR_EOF);
	else if (ret == FUNCT_SUCCESS)
		return (FUNCT_SUCCESS);
	else if (input_read_ansi(data) == FUNCT_FAILURE)
	{
		ret = input_parse_special(data);
		if (ret == FUNCT_FAILURE)
		{
			if (input_parse_char(data) == FUNCT_ERROR)
				return (reset_input_read_return(data, FUNCT_ERROR));
		}
		if (ret == FUNCT_ERROR)
			return (reset_input_read_return(data, FUNCT_ERROR));
	}
	return (FUNCT_SUCCESS);
}

int			input_read_from_buffer(t_vshdata *data)
{
	if (data->line->buffer != NULL)
	{
		if (data->line->buffer[data->line->buffer_i] != '\0')
		{
			data->input->c = data->line->buffer[data->line->buffer_i];
			data->line->buffer_i++;
		}
		else
		{
			ft_strdel(&data->line->buffer);
			data->line->buffer = NULL;
			data->line->buffer_i = 0;
			return (FUNCT_FAILURE);
		}
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}

/*
**	During the readloop, signals will be ignored. This means that pressing
**	ctrl+c will result in a `\3` char sent to the shell. Likewise, ctrl+d
**	will result in a '\4' char being sent to the shell. Consequently, you
**	are not able to send most common signals to the shell while input is being
**	read.
**
**	Input will by read on a byte-by-byte basis. Each time a character is read,
**	we will parse it in the function above. If the parsed char was an '\n', it
**	means that input_read is done.
*/

int			input_read(t_vshdata *data)
{
	int		ret;

	if (data == NULL)
		return (FUNCT_ERROR);
	data->line->line = ft_strnew(data->line->len_max);
	if (data->line->line == NULL)
		return (reset_input_read_return(data, FUNCT_ERROR));
	reset_input_read_return(data, 0);
	term_disable_isig(data->term->termios_p);
	while (true)
	{
		if (input_read_from_buffer(data) != FUNCT_SUCCESS &&
			read(STDIN_FILENO, &data->input->c, 1) == -1)
			return (reset_input_read_return(data, FUNCT_ERROR));
		ret = input_parse(data);
		if (ret == NEW_PROMPT || ret == FUNCT_ERROR || ret == IR_EOF)
			return (ret);
		if (data->input->c == '\n')
		{
			curs_go_end(data);
			break ;
		}
	}
	term_enable_isig(data->term->termios_p);
	return (reset_input_read_return(data, FUNCT_SUCCESS));
}
