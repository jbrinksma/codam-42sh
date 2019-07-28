/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_alias_set.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/24 17:30:55 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/25 15:44:48 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int			sort_by_name(t_aliaslst *env1, t_aliaslst *env2)
{
	return (ft_strcmp(env1->var, env2->var) > 0);
}

static t_aliaslst	*builtin_alias_new(char *var)
{
	t_aliaslst	*new;

	new = (t_aliaslst*)ft_memalloc(sizeof(t_aliaslst));
	if (new == NULL)
		return (NULL);
	new->var = ft_strdup(var);
	if (new->var == NULL)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

static void			builtin_alias_add(t_aliaslst *new, t_aliaslst **aliaslst)
{
	t_aliaslst	*probe;

	if (sort_by_name(*aliaslst, new) == true)
	{
		new->next = *aliaslst;
		*aliaslst = new;
		return ;
	}
	probe = *aliaslst;
	while (probe != NULL)
	{
		if (probe->next == NULL)
		{
			probe->next = new;
			break ;
		}
		if (sort_by_name(probe->next, new) == true)
		{
			new->next = probe->next;
			probe->next = new;
			break ;
		}
		probe = probe->next;
	}
}

int					builtin_alias_set(char *arg, t_aliaslst **aliaslst)
{
	t_aliaslst	*probe;
	t_aliaslst	*new;
	int			name_len;

	name_len = ft_strchr(arg, '=') - arg;
	probe = *aliaslst;
	while (probe != NULL)
	{
		if (ft_strnequ(arg, probe->var, name_len) == true &&
			(probe->var[name_len] == '='))
		{
			ft_strdel(&probe->var);
			probe->var = ft_strdup(arg);
			return (probe->var != NULL ? FUNCT_SUCCESS : FUNCT_ERROR);
		}
		probe = probe->next;
	}
	new = builtin_alias_new(arg);
	if (new == NULL)
		return (FUNCT_ERROR);
	if (*aliaslst == NULL)
		*aliaslst = new;
	else
		builtin_alias_add(new, aliaslst);
	return (FUNCT_SUCCESS);
}
