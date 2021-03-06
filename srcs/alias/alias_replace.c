/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias_replace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/26 20:29:50 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/30 11:30:57 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	alias_remove_newlines replaces every newline with an semicol token
**	when there are multiple newlines, only the first will be replaced
**	others will be removed
**	only the last newline remaines and is removed in alias_combine_tokenlsts
*/

static void	alias_remove_newlines(t_tokenlst *new_tokenlst)
{
	t_tokenlst *del_node;

	while (new_tokenlst->next->type != END)
	{
		if (new_tokenlst->type == NEWLINE)
		{
			new_tokenlst->type = SEMICOL;
			while (new_tokenlst->next->type == NEWLINE &&
				new_tokenlst->next->next->type != END)
			{
				del_node = new_tokenlst->next;
				new_tokenlst->next = new_tokenlst->next->next;
				ft_memdel((void**)&del_node);
			}
		}
		new_tokenlst = new_tokenlst->next;
	}
}

/*
**	If an alias is set to nothing alias_remove_tk_from_lst well be called
**	it will remove the original token from the token lst
**	and replace it with nothing
*/

static void	alias_remove_tk_from_lst(t_tokenlst *probe,
			t_tokenlst *new_tokenlst)
{
	t_tokenlst *next_after_alias;

	lexer_tokenlstdel(&new_tokenlst);
	next_after_alias = probe->next->next;
	ft_strdel(&probe->next->value);
	ft_memdel((void**)&probe->next);
	probe->next = next_after_alias;
}

/*
**	alias_combine_tokenlsts inserts the newlist into the main lst
**	before combining the two lsts alias_remove_newlines is called and
**	it removes the start, last newline, and end token from newlst
*/

static void	alias_combine_tokenlsts(t_tokenlst *probe, t_tokenlst *new_tokenlst)
{
	t_tokenlst *start_end;

	if (new_tokenlst->next->type == END)
		return (alias_remove_tk_from_lst(probe, new_tokenlst));
	alias_remove_newlines(new_tokenlst);
	start_end = new_tokenlst;
	new_tokenlst = new_tokenlst->next;
	ft_memdel((void**)&start_end);
	start_end = new_tokenlst;
	while (start_end->next->type != NEWLINE && start_end->next->type != END)
		start_end = start_end->next;
	ft_memdel((void**)&start_end->next->next);
	ft_memdel((void**)&start_end->next);
	start_end->next = probe->next->next;
	ft_strdel(&probe->next->value);
	ft_memdel((void**)&probe->next);
	probe->next = new_tokenlst;
}

/*
**	alias_init_line sets alias value to data line line
**	if there are any new lines at the beginning we will skip them
*/

static int	alias_init_line(t_vshdata *data, char *alias_equal)
{
	if (alias_equal == NULL)
		return (FUNCT_ERROR);
	ft_strdel(&data->line->line);
	alias_equal++;
	while (*alias_equal == '\n')
		alias_equal++;
	data->line->line = ft_strdup(alias_equal);
	if (data->line->line == NULL)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

/*
**	alias_replace will lex the string of alias='string' and
**	insert it into the old token list
**	it also adds the expanded alias to the expanded list
**	so it won't be expanded again
*/

int			alias_replace(t_vshdata *data, t_tokenlst *probe, char *alias,
			char **expanded)
{
	char		*alias_equal;
	char		**new_expanded;
	t_tokenlst	*new_tokenlst;

	alias_equal = ft_strchr(alias, '=');
	new_tokenlst = NULL;
	if (alias_init_line(data, alias_equal) == FUNCT_ERROR ||
		shell_close_quote_and_esc(data) == FUNCT_ERROR ||
		lexer(&data->line->line, &new_tokenlst) == FUNCT_ERROR ||
		shell_dless_input(data, &new_tokenlst) == FUNCT_ERROR)
		return (alias_error(&data->line->line, &new_tokenlst, NULL));
	new_expanded = alias_add_expanded(expanded, alias, alias_equal);
	if (new_expanded == NULL)
		return (alias_error(&data->line->line, &new_tokenlst, &new_expanded));
	if (alias_expansion(data, &new_tokenlst, new_expanded) == FUNCT_ERROR)
		return (alias_error(&data->line->line, &new_tokenlst, &new_expanded));
	ft_strarrdel(&new_expanded);
	alias_combine_tokenlsts(probe, new_tokenlst);
	return (FUNCT_SUCCESS);
}
