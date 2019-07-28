/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unalias.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/24 14:41:55 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/25 15:44:12 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	builtin_unalias_find_and_del(char *arg,
	int arg_len, t_aliaslst **aliaslst)
{
	t_aliaslst *del;
	t_aliaslst *probe;

	probe = *aliaslst;
	if (ft_strnequ(arg, (*aliaslst)->var, arg_len) == true &&
		((*aliaslst)->var[arg_len] == '='))
	{
		*aliaslst = (*aliaslst)->next;
		builtin_alias_delnode(&probe);
		return (FUNCT_SUCCESS);
	}
	while (probe->next != NULL)
	{
		if (ft_strnequ(arg, probe->next->var, arg_len) == true &&
			(probe->next->var[arg_len] == '='))
		{
			del = probe->next;
			probe->next = probe->next->next;
			builtin_alias_delnode(&del);
			return (FUNCT_SUCCESS);
		}
		probe = probe->next;
	}
	return (FUNCT_FAILURE);
}

static void	builtin_unalias_args(char **args, int i, t_aliaslst **aliaslst)
{
	int		arg_len;

	while (args[i] != NULL)
	{
		arg_len = ft_strlen(args[i]);
		if (*aliaslst == NULL || builtin_unalias_find_and_del(args[i],
			arg_len, aliaslst) == FUNCT_FAILURE)
		{
			ft_eprintf("vsh: unalias: %s: not found\n", args[i]);
			g_state->exit_code = EXIT_FAILURE;
		}
		i++;
	}
}

static int	builtin_unalias_flag(char **args, int *flag, int *i)
{
	int j;

	while (args[*i] != NULL)
	{
		j = 1;
		if (args[*i][0] != '-' || args[*i][1] == '\0')
			return (FUNCT_SUCCESS);
		while (args[*i][j] != '\0')
		{
			if (args[*i][j] != 'a')
			{
				ft_eprintf("vsh: unalias: -%c: invalid option\n", args[*i][j]);
				ft_eprintf("unalias: usage: unalias [-a] name [name ...]\n");
				return (FUNCT_FAILURE);
			}
			(*flag) |= UNALIAS_FLAG_LA;
			j++;
		}
		(*i)++;
	}
	return (FUNCT_SUCCESS);
}

void		builtin_unalias(char **args, t_aliaslst **aliaslst)
{
	int		flag;
	int		i;

	i = 1;
	flag = 0;
	g_state->exit_code = EXIT_FAILURE;
	if (args[1] == NULL)
	{
		ft_eprintf("unalias: usage: unalias [-a] name [name ...]\n");
		return ;
	}
	if (builtin_unalias_flag(args, &flag, &i) == FUNCT_FAILURE)
		return ;
	g_state->exit_code = EXIT_SUCCESS;
	if (flag & UNALIAS_FLAG_LA)
		builtin_alias_lstdel(aliaslst);
	else
		builtin_unalias_args(args, i, aliaslst);
}
