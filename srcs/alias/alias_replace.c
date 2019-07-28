/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias_replace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/26 20:29:50 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/28 17:17:12 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	alias_combine_tokenlsts(t_tokenlst *probe, t_tokenlst *new_tokenlst)
{
	t_tokenlst *start_end;

	start_end = new_tokenlst;
	new_tokenlst = new_tokenlst->next;
	ft_memdel((void**)&start_end);
	start_end = new_tokenlst;
	while (start_end->next->type != END)
		start_end = start_end->next;
	ft_memdel((void**)&start_end->next);
	start_end->next = probe->next->next;
	ft_memdel((void**)&probe->next);
	probe->next = new_tokenlst;
}

int			alias_error(t_tokenlst **tokenlst, char **expanded)
{
	if (expanded != NULL)
		ft_strarrdel(&expanded);
	lexer_tokenlstdel(tokenlst);
	return (FUNCT_ERROR);
}

static char	**alias_malloc_expanded(char **expanded, int *i)
{
	char		**new_expanded;

	if (expanded == NULL)
		new_expanded = (char **)ft_memalloc(sizeof(char *) * 2);
	else
	{
		while (expanded[*i] != NULL)
			(*i)++;
		new_expanded = (char **)ft_memalloc(sizeof(char *) * (*i + 2));
	}
	return (new_expanded);
}

char		**alias_add_expanded(char **expanded, char *alias,
			char *alias_equal)
{
	char		**new_expanded;
	char		*alias_key;
	int			i;
	int			new_i;

	i = 0;
	new_expanded = alias_malloc_expanded(expanded, &i);
	alias_key = ft_strndup(alias, alias_equal - alias);
	if (new_expanded == NULL || alias_key == NULL)
		return (NULL);
	new_i = 0;
	while (new_i < i)
	{
		new_expanded[new_i] = ft_strdup(expanded[new_i]);
		if (new_expanded[new_i] == NULL)
		{
			ft_strarrdel(&new_expanded);
			return (NULL);
		}
		new_i++;
	}
	new_expanded[new_i] = alias_key;
	return (new_expanded);
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
	new_line = ft_strdup(alias_equal + 1);
	new_tokenlst = NULL;
	if (new_line == NULL || shell_quote_checker(vshdata, &new_line, &status)
		== FUNCT_ERROR || lexer(&new_line, &new_tokenlst) != FUNCT_SUCCESS ||
		shell_dless_input(vshdata, &new_tokenlst) != FUNCT_SUCCESS)
		return (FUNCT_ERROR);
	new_expanded = alias_add_expanded(expanded, alias, alias_equal);
	if (new_expanded == NULL)
		return (FUNCT_ERROR);
	if (alias_expansion(vshdata, &new_tokenlst, new_expanded) == FUNCT_ERROR)
		return (alias_error(&new_tokenlst, new_expanded));
	ft_strarrdel(&new_expanded);
	alias_combine_tokenlsts(probe, new_tokenlst);
	return (FUNCT_SUCCESS);
}
