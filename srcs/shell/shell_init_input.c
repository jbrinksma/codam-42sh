/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init_input.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/04 10:22:44 by rkuijper       #+#    #+#                */
/*   Updated: 2019/09/04 11:45:48 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

t_datacurs		*shell_init_vshdatacurs(void)
{
	t_datacurs	*curs;

	curs = ft_memalloc(sizeof(t_datacurs));
	if (curs == NULL)
		return (NULL);
	curs->coords = (t_point){ 1, 1 };
	curs->cur_ws_col = UNINIT;
	curs->cur_ws_row = UNINIT;
	return (curs);
}

t_dataline		*shell_init_vshdataline(void)
{
	t_dataline	*line;

	line = ft_memalloc(sizeof(t_dataline));
	if (line == NULL)
		return (NULL);
	line->len_max = 64;
	return (line);
}

t_dataprompt	*shell_init_vshdataprompt(void)
{
	t_dataprompt	*prompt;

	prompt = ft_memalloc(sizeof(t_dataprompt));
	if (prompt == NULL)
		return (NULL);
	prompt->cur_prompt_type = REGULAR_PROMPT;
	prompt->prompt_name = PROMPT_NAME;
	prompt->prompt_seperator = PROMPT_SEPERATOR;
	prompt->prompt_len = ft_strlen(prompt->prompt_name) +
		ft_strlen(prompt->prompt_seperator);
	return (prompt);
}

t_datainput		*shell_init_vshdatainput(void)
{
	t_datainput	*input;

	input = ft_memalloc(sizeof(t_datainput));
	if (input == NULL)
		return (NULL);
	return (input);
}

t_datatermcaps	*shell_init_vshdatatermcaps(void)
{
	t_datatermcaps	*termcaps;

	termcaps = ft_memalloc(sizeof(t_datatermcaps));
	if (termcaps == NULL)
		return (NULL);
	termcaps->tc_clear_lines_str = tgetstr("cd", NULL);
	if (termcaps->tc_clear_lines_str == NULL)
	{
		ft_memdel((void**)&termcaps);
		return (NULL);
	}
	termcaps->tc_scroll_down_str = tgetstr("sf", NULL);
	if (termcaps->tc_scroll_down_str == NULL)
	{
		ft_strdel(&termcaps->tc_clear_lines_str);
		ft_memdel((void**)&termcaps);
		return (NULL);
	}
	return (termcaps);
}
