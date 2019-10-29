/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_read_ansi.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/30 10:45:52 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/29 12:23:49 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	input_parse_ansi_arrows(t_vshdata *data,
	char termcapbuf[TERMCAPBUFFSIZE])
{
	int		ret;

	ret = FUNCT_SUCCESS;
	if (ft_strequ(termcapbuf, TC_LEFT_ARROW) == true)
		curs_move_left(data);
	else if (ft_strequ(termcapbuf, TC_RIGHT_ARROW) == true)
		curs_move_right(data);
	else if (ft_strequ(termcapbuf, TC_UP_ARROW) == true)
		ret = history_change_line(data, ARROW_UP);
	else if (ft_strequ(termcapbuf, TC_DOWN_ARROW) == true)
		ret = history_change_line(data, ARROW_DOWN);
	else if (ft_strequ(termcapbuf, TC_CTRL_RIGHT_ARROW) == true)
		curs_move_next_word(data);
	else if (ft_strequ(termcapbuf, TC_CTRL_LEFT_ARROW) == true)
		curs_move_prev_word(data);
	else if (ft_strequ(termcapbuf, TC_CTRL_UP_ARROW) == true)
		curs_move_up(data);
	else if (ft_strequ(termcapbuf, TC_CTRL_DOWN_ARROW) == true)
		curs_move_down(data);
	else
		return (FUNCT_FAILURE);
	if (ret == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

static int	input_ctrlr_esc(t_vshdata *data)
{
	if (input_parse_esc(data) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	input_empty_buffer(data, 0);
	return (FUNCT_SUCCESS);
}

/*
**	Is called after reading '\e'. The complete sequence is dumped into a buf.
**	If we support the escape sequence, it is handled by any of the functions
**	below, otherwise it is ignored.
*/

int			input_read_ansi(t_vshdata *data)
{
	char	termcapbuf[TERMCAPBUFFSIZE];
	int		ret;

	ft_bzero(termcapbuf, TERMCAPBUFFSIZE);
	if (data->input->c == '\e')
	{
		if (data->input->searchhistory.active)
			return (input_ctrlr_esc(data));
		termcapbuf[0] = '\e';
		if (read(STDIN_FILENO, &termcapbuf[1], TERMCAPBUFFSIZE - 1) == -1)
			return (FUNCT_ERROR);
		ret = input_parse_ansi_arrows(data, termcapbuf);
		if (ret == FUNCT_FAILURE)
		{
			if (ft_strequ(termcapbuf, TC_HOME) == true)
				curs_go_home(data);
			else if (ft_strequ(termcapbuf, TC_END) == true)
				curs_go_end(data);
			else if (ft_strequ(termcapbuf, TC_DELETE) == true)
				input_handle_delete(data);
			else
				return (FUNCT_FAILURE);
			return (FUNCT_SUCCESS);
		}
		return (ret);
	}
	return (FUNCT_FAILURE);
}
