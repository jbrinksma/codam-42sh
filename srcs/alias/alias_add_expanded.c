/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias_add_expanded.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/01 13:26:37 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/01 17:15:54 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

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

static char	**alias_error_expaneded(char **expanded)
{
	if (expanded != NULL)
		ft_strarrdel(&expanded);
	return (NULL);
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
		return (alias_error_expaneded(new_expanded));
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
