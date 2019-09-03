/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/12 14:09:10 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/02 12:16:49 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	auto_lstdel(void *str, size_t size)
{
	(void)size;
	ft_strdel((char**)&str);
}

char	*auto_get_file_str(char *line, ssize_t i)
{
	ssize_t	i_cursor;
	char	*match;

	i_cursor = i;
	i--;
	while (i >= 0)
	{
		if (tools_isidentifierchar(line[i]) == false &&
			line[i] != '/' && line[i] != '.')
			break ;
		i--;
	}
	match = ft_strnew(i_cursor - i);
	if (match == NULL)
	{
		ft_eprintf(E_ALLOC_STR);
		return (NULL);
	}
	ft_strncpy(match, &line[i + 1], (i_cursor - i) - 1);
	match[i_cursor - i] = '\0';
	return (match);
}

char	*auto_get_match_str(char *line, ssize_t i)
{
	int		i_cursor;
	char	*match;

	i_cursor = i;
	i--;
	while (i >= 0)
	{
		if (tools_isidentifierchar(line[i]) == false)
			break ;
		i--;
	}
	match = ft_strnew(i_cursor - i);
	if (match == NULL)
	{
		ft_eprintf(E_ALLOC_STR);
		return (NULL);
	}
	ft_strncpy(match, &line[i + 1], (i_cursor - i) - 1);
	match[i_cursor - i] = '\0';
	return (match);
}

void	auto_print_line(t_vshdata *data)
{
	int		old_index;

	old_index = data->line->index;
	shell_display_prompt(data, data->prompt->cur_prompt_type);
	data->curs->coords = (t_point){ data->prompt->prompt_len + 1, 1 };
	input_print_str(data, data->line->line);
	data->line->index = data->line->len_cur;
	curs_move_n_left(data, data->line->index - old_index);
}

void	auto_start(t_vshdata *data)
{
	int		state;
	char	*match;
	t_list	*matchlst;

	if (data->line->line == NULL)
		return ;
	state = auto_find_state(data->line->line, data->line->index);
	match = NULL;
	matchlst = NULL;
	if (state == STATE_CMD)
		match = auto_get_match_str(data->line->line, data->line->index);
	else if (state == STATE_VAR)
		match = auto_get_match_str(data->line->line, data->line->index);
	else if (state == STATE_FILE)
		match = auto_get_file_str(data->line->line, data->line->index);
	if (match == NULL ||
		auto_find_matches(data, &match, &matchlst, state) == FUNCT_ERROR)
		state = FUNCT_ERROR;
	else
		state = auto_handle_matchlst(data, match, &matchlst);
	if (state != AUTO_NO_MATCHES && state != AUTO_ADDED_MATCH)
		auto_print_line(data);
	ft_strdel(&match);
	ft_lstdel(&matchlst, &auto_lstdel);
}
