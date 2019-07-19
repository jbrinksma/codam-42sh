/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_remove_tmp.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/18 12:14:39 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/19 20:55:27 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void env_node_del(t_envlst **node)
{
	ft_strdel(&(*node)->var);
	ft_memdel((void**)node);
}

void        env_remove_tmp(t_envlst *env)
{
    t_envlst *tmp;

    if (env == NULL || env->next == NULL)
        return ;
    if (env->next->type == ENV_TEMP)
    {
        tmp = env->next;
        env->next = env->next->next;
        env_node_del(&tmp);
        env_remove_tmp(env);
    }
    else
        env_remove_tmp(env->next);
}
