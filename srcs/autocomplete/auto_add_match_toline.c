/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_add_match_toline.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/12 20:55:01 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/07 11:38:49 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	This function inserts the found match into line
**	to_add is the part that has to be added at the cursor position
**	New line = everything before the cursor + to_add + anything after the cursor
*/

int		auto_add_match_toline(char *match, char *to_add, t_vshdata *data)
{
	int		old_index;
	int		match_len;
	int		to_add_len;
	char	*new_line;

	match_len = ft_strlen(match);
	to_add_len = ft_strlen(to_add);
	new_line = ft_strnew(data->line->len_cur - match_len + to_add_len);
	if (new_line == NULL)
		return (err_ret(E_ALLOC_STR));
	data->line->len_max = data->line->len_cur - match_len + to_add_len;
	ft_strncpy(new_line, data->line->line, data->line->index - match_len);
	ft_strcat(new_line, to_add);
	ft_strcat(new_line, &(data->line->line)[data->line->index]);
	ft_strdel(&(data->line->line));
	data->line->line = new_line;
	data->line->len_cur = ft_strlen(data->line->line);
	old_index = data->line->index;
	input_print_str(data, &data->line->line[data->line->index]);
	data->line->index = data->line->len_cur;
	curs_move_n_left(data, data->line->len_cur -
		(old_index - (match_len - to_add_len)));
	return (AUTO_ADDED_MATCH);
}
