/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias_replace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/26 20:29:50 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/22 10:46:24 by omulder       ########   odam.nl         */
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
**	alias_combine_tokenlsts inserts the newlist into the main lst
**	before combining the two lsts alias_remove_newlines is called and
**	it removes the start, last newline, and end token from newlst
*/

static void	alias_combine_tokenlsts(t_tokenlst *probe, t_tokenlst *new_tokenlst)
{
	t_tokenlst *start_end;

	alias_remove_newlines(new_tokenlst);
	start_end = new_tokenlst;
	new_tokenlst = new_tokenlst->next;
	ft_memdel((void**)&start_end);
	start_end = new_tokenlst;
	while (start_end->next->type != NEWLINE)
		start_end = start_end->next;
	ft_memdel((void**)&start_end->next->next);
	ft_memdel((void**)&start_end->next);
	start_end->next = probe->next->next;
	ft_strdel(&probe->next->value);
	ft_memdel((void**)&probe->next);
	probe->next = new_tokenlst;
}

int			alias_error(char **line, t_tokenlst **tokenlst, char ***expanded)
{
	ft_eprintf(E_N_ALLOC_STR, "alias");
	if (expanded != NULL && *expanded != NULL)
		ft_strarrdel(expanded);
	if (tokenlst != NULL && *tokenlst != NULL)
		lexer_tokenlstdel(tokenlst);
	if (line != NULL && *line != NULL)
		ft_strdel(line);
	return (FUNCT_ERROR);
}

int			alias_replace(t_vshdata *vshdata, t_tokenlst *probe, char *alias,
			char **expanded)
{
	char		*new_line;
	char		*alias_equal;
	char		**new_expanded;
	t_tokenlst	*new_tokenlst;
	int			status; // This may or may not need to get fixed

	status = 1;
	alias_equal = ft_strchr(alias, '=');
	new_line = ft_strjoin(alias_equal + 1, "\n");
	new_tokenlst = NULL;
	if (new_line == NULL || shell_close_quote_and_esc(vshdata, &new_line,
		&status) == FUNCT_ERROR
		|| lexer(&new_line, &new_tokenlst) == FUNCT_ERROR
		|| shell_dless_input(vshdata, &new_tokenlst) == FUNCT_ERROR)
		return (alias_error(&new_line, &new_tokenlst, NULL));
	new_expanded = alias_add_expanded(expanded, alias, alias_equal);
	if (new_expanded == NULL)
		return (alias_error(&new_line, &new_tokenlst, &new_expanded));
	if (alias_expansion(vshdata, &new_tokenlst, new_expanded) == FUNCT_ERROR)
		return (alias_error(&new_line, &new_tokenlst, &new_expanded));
	ft_strarrdel(&new_expanded);
	alias_combine_tokenlsts(probe, new_tokenlst);
	return (FUNCT_SUCCESS);
}
