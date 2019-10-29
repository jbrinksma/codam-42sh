/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_r.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/23 15:01:03 by omulder        #+#    #+#                */
/*   Updated: 2019/10/28 15:51:44 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

/*
**  Used to clear the regular prompt and line.
*/

static void	clear_line(t_vshdata *data)
{
	char *tmp;

	curs_move_n_left(data, data->line->index);
	data->line->index = data->prompt->prompt_len;
	tmp = data->line->line;
	data->line->line = "";
	curs_move_n_left(data, data->prompt->prompt_len);
	data->line->line = tmp;
	tputs(data->termcaps->tc_clear_lines_str, 1, &ft_tputchar);
}

/*
**  Clears the prompt and prints the basic ctrl+r prompt. Also initializes a new
**  empty line.
*/

static int	init(t_vshdata *data)
{
	int index_tmp;

	index_tmp = data->line->index;
	data->input->searchhistory.current = data->history->tail;
	clear_line(data);
	input_print_str(data, HIST_SRCH_FIRST "" HIST_SRCH_LAST);
	input_print_str(data, data->line->line);
	data->line->index = data->line->len_cur;
	curs_move_n_left(data, data->line->len_cur - index_tmp);
	data->input->searchhistory.total_len =
	ft_strlen(HIST_SRCH_FIRST "" HIST_SRCH_LAST) + index_tmp;
	data->input->searchhistory.result_str = data->line->line;
	data->input->searchhistory.result_i = ft_strlen(data->line->line) - 1;
	data->line->index = 0;
	data->line->len_max = 64;
	data->line->len_cur = 0;
	data->line->line = ft_strnew(data->line->len_max);
	if (data->line->line == NULL)
	{
		return (err_ret_prog_exit(E_N_ALLOC_STR, "reverse-i-search",
		EXIT_FAILURE));
	}
	data->input->searchhistory.active = true;
	return (FUNCT_SUCCESS);
}

/*
**	Gets called after clearing the whole line, prints all the stuff again
**  where `first` is the user input and `second` is the found match or the
**  string that was already in line.
**
**  Does some magic with the variables that hold the length of line and prompt
**  to make sure all the input_ functions actually do what they have to do.
**  This is mostly needed to support multiline.
*/

void		input_print_ctrl_r(t_vshdata *data, char *first, char *second,
int second_i)
{
	int		first_len;
	int		prompt_len;

	first_len = ft_strlen(first);
	prompt_len = ft_strlen(HIST_SRCH_FIRST "" HIST_SRCH_LAST);
	input_print_str(data, HIST_SRCH_FIRST);
	input_print_str(data, first);
	input_print_str(data, HIST_SRCH_LAST);
	input_print_str(data, second);
	data->line->index = ft_strlen(second);
	data->line->line = second;
	data->prompt->prompt_len = prompt_len + first_len;
	curs_move_n_left(data, data->line->index - second_i);
	data->line->line = first;
	data->input->searchhistory.total_len = prompt_len + first_len + second_i;
	data->line->index = first_len;
}

/*
**  Get's called every time ctrl+r is pressed. The first time only the init
**  function is executed. When pressed after the first time it wil find and
**  display the next match.
*/

int			input_parse_ctrl_r(t_vshdata *data)
{
	if (data->input->searchhistory.active)
	{
		if (ctrlr_clear_line(data) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		if (data->input->searchhistory.current != NULL)
			data->input->searchhistory.current =
			data->input->searchhistory.current->prev;
		if (history_ctrl_r(data, true) == FUNCT_ERROR)
			return (FUNCT_SUCCESS);
		input_print_ctrl_r(data, data->line->line,
		data->input->searchhistory.result_str,
		data->input->searchhistory.result_i);
	}
	else
		return (init(data));
	return (FUNCT_SUCCESS);
}
