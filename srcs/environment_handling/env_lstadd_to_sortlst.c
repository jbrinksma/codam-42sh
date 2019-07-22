/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstadd_to_sortlst.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/20 18:49:15 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/20 19:14:03 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	sort_by_value(t_envlst *env1, t_envlst *env2)
{
	return (ft_strcmp(env1->var, env2->var) > 0);
}

void		env_lstadd_to_sortlst(t_envlst *envlst, t_envlst *new)
{
	while (envlst != NULL)
	{
		if (envlst->next == NULL)
		{
			envlst->next = new;
			break ;
		}
		if (sort_by_value(envlst->next, new) == true)
		{
			new->next = envlst->next;
			envlst->next = new;
			break ;
		}
		envlst = envlst->next;
	}
}
