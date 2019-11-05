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
#include <sys/ioctl.h>

t_datacurs		*shell_init_vshdatacurs(void)
{
	struct winsize	ws;
	t_datacurs		*curs;

	curs = ft_memalloc(sizeof(t_datacurs));
	if (curs == NULL)
		return (NULL);
	curs->coords = (t_point){ 1, 1 };
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) != -1)
	{
		curs->cur_ws_col = ws.ws_col;
		curs->cur_ws_row = ws.ws_row;
	}
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
	termcaps->tc_scroll_down_str = tgetstr("sf", NULL);
	return (termcaps);
}
