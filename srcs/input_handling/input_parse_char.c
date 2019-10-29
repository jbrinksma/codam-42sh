/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_char.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:33:54 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/28 16:08:54 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "term.h"

/*
**  Clears the full line including prompt when ctrl+r is active. The line
**  consists of 4 parts:
**  HIST_SRCH_FIRST - input(line) - HIST_SRCH_LAST - result_str
**  which are all cleared.
**  The crazy way it uses to do this is to make sure multiline is supported.
*/

int			ctrlr_clear_line(t_vshdata *data)
{
	char *tmp;

	tmp = data->line->line;
	data->line->line = ft_strjoinfree_s2(HIST_SRCH_FIRST,
	ft_strjoinfree_s2(tmp,
	ft_strjoin(HIST_SRCH_LAST, data->input->searchhistory.result_str)));
	if (data->line->line == NULL)
	{
		return (err_ret_prog_exit(E_N_ALLOC_STR, "reverse-i-search",
		EXIT_FAILURE));
	}
	data->line->index = data->input->searchhistory.total_len;
	data->prompt->prompt_len = 0;
	curs_move_n_left(data, data->line->index);
	ft_strdel(&data->line->line);
	data->line->line = tmp;
	tputs(data->termcaps->tc_clear_lines_str, 1, &ft_tputchar);
	return (FUNCT_SUCCESS);
}

/*
**  If ctrl+r is active -> clear the line, add the char, search again
**  starting from the last match, print the result. If char is '\n' end the
**  ctrl+r execution.
**  If ctrl+r is not active the regular parse_char function is called.
*/

int			input_parse_char(t_vshdata *data)
{
	if (data->input->searchhistory.active)
	{
		if (ctrlr_clear_line(data) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		data->line->index = ft_strlen(data->line->line);
		if (input_parse_char_og(data) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		if (data->input->searchhistory.active == false)
			return (FUNCT_SUCCESS);
		if (history_ctrl_r(data, false) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		input_print_ctrl_r(data, data->line->line,
		data->input->searchhistory.result_str,
		data->input->searchhistory.result_i);
	}
	else
		input_parse_char_og(data);
	return (FUNCT_SUCCESS);
}
