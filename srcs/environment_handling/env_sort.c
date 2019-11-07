/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_sort.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/20 18:18:07 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/06 13:31:25 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int		env_is_sorted(t_envlst *env1, t_envlst *env2)
{
	return (ft_strcmp(env1->var, env2->var) > 0);
}

static void		split_envlst(t_envlst **env, t_envlst **half)
{
	t_envlst *probe_to_middle;
	t_envlst *probe_to_end;

	probe_to_middle = *env;
	probe_to_end = (*env)->next;
	while (probe_to_end != NULL)
	{
		probe_to_end = probe_to_end->next;
		if (probe_to_end != NULL)
		{
			probe_to_middle = probe_to_middle->next;
			probe_to_end = probe_to_end->next;
		}
	}
	*half = probe_to_middle->next;
	probe_to_middle->next = NULL;
}

static t_envlst	*merge_lst(t_envlst *env, t_envlst *half,
				int (*sort)(t_envlst *, t_envlst *))
{
	t_envlst *result;

	if (env == NULL)
		return (half);
	if (half == NULL)
		return (env);
	if (sort(env, half) == false)
	{
		result = env;
		result->next = merge_lst(env->next, half, sort);
	}
	else
	{
		result = half;
		result->next = merge_lst(env, half->next, sort);
	}
	return (result);
}

static void		env_lstsort(t_envlst **env, int (*sort)(t_envlst *, t_envlst *))
{
	t_envlst *half;

	if (*env == NULL || (*env)->next == NULL)
		return ;
	split_envlst(env, &half);
	env_lstsort(env, sort);
	env_lstsort(&half, sort);
	*env = merge_lst(*env, half, sort);
}

void			env_sort(t_envlst *head)
{
	env_lstsort(&head->next, env_is_sorted);
}
