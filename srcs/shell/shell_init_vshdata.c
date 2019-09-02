/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init_vshdata.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/29 12:42:44 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/30 16:02:26 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

t_vshdatacurs	*shell_init_vshdatacurs(void)
{
	t_vshdatacurs	*curs;

	curs = ft_memalloc(sizeof(t_vshdatacurs));
	if (curs == NULL)
		return (NULL);
	curs->coords = (t_point){ 1, 1 };
	curs->cur_ws_col = UNINIT;
	curs->cur_ws_row = UNINIT;
	return (curs);
}

t_vshdataline	*shell_init_vshdataline(void)
{
	t_vshdataline	*line;

	line = ft_memalloc(sizeof(t_vshdataline));
	if (line == NULL)
		return (NULL);
	line->len_max = 64;
	return (line);
}

t_vshdataprompt	*shell_init_vshdataprompt(void)
{
	t_vshdataprompt	*prompt;

	prompt = ft_memalloc(sizeof(t_vshdataprompt));
	if (prompt == NULL)
		return (NULL);
	prompt->cur_prompt_type = REGULAR_PROMPT;
	prompt->prompt_name = PROMPT_NAME;
	prompt->prompt_seperator = PROMPT_SEPERATOR;
	prompt->prompt_len = ft_strlen(prompt->prompt_name) +
		ft_strlen(prompt->prompt_seperator);
	return (prompt);
}

t_vshdatainput	*shell_init_vshdatainput(void)
{
	t_vshdatainput	*input;

	input = ft_memalloc(sizeof(t_vshdatainput));
	if (input == NULL)
		return (NULL);
	return (input);
}

t_vshdatahashtable	*shell_init_vshdatahashtable(void)
{
	t_vshdatahashtable	*hashtable;

	hashtable = ft_memalloc(sizeof(t_vshdatahashtable));
	if (hashtable == NULL)
		return (NULL);
	return (hashtable);
}

t_vshdatahistory	*shell_init_vshdatahistory(void)
{
	t_vshdatahistory	*history;

	history = ft_memalloc(sizeof(t_vshdatahistory));
	if (history == NULL)
		return (NULL);
	return (history);
}

t_vshdataalias	*shell_init_vshdataalias(void)
{
	t_vshdataalias	*alias;

	alias = ft_memalloc(sizeof(t_vshdataalias));
	if (alias == NULL)
		return (NULL);
	alias->alias_file = ALIASFILENAME;
	return (alias);
}

t_vshdatatermcaps	*shell_init_vshdatatermcaps(void)
{
	t_vshdatatermcaps	*termcaps;

	termcaps = ft_memalloc(sizeof(t_vshdatatermcaps));
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

t_vshdata	*shell_init_vshdata(void)
{
	t_vshdata *data;

	data = ft_memalloc(sizeof(t_vshdata));
	if (data == NULL)
	{
		ft_eprintf(E_ALLOC_STR);
		return (NULL);
	}
	data->envlst = env_getlst();
	if (data->envlst == NULL)
	{
		ft_eprintf(E_ALLOC_STR);
		return (NULL);
	}
	data->term = term_prepare(data->envlst);
	data->curs = shell_init_vshdatacurs();
	data->history = shell_init_vshdatahistory();
	data->line = shell_init_vshdataline();
	data->prompt = shell_init_vshdataprompt();
	data->input = shell_init_vshdatainput();
	data->hashtable = shell_init_vshdatahashtable();
	data->alias = shell_init_vshdataalias();
	data->termcaps = shell_init_vshdatatermcaps();
	if (data->term == NULL || data->curs == NULL
		|| data->history == NULL || data->line == NULL || data->prompt == NULL
		|| data->input == NULL || data->hashtable == NULL || data->alias == NULL
		|| data->termcaps == NULL)
	{
		ft_eprintf(E_ALLOC_STR);
		return (NULL);
	}
	if (shell_init_files(data) == FUNCT_ERROR
		|| history_get_file_content(data) == FUNCT_ERROR
		|| alias_read_file(data) == FUNCT_ERROR)
		return (NULL);
	return (data);
}
