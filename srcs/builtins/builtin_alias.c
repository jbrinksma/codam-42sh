/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_alias.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/24 13:36:44 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/30 10:26:00 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	alias [-p] [name[=value] ...]
**	
**	The name cannot contain any special shell characters
**	When -p is set, alias prints all aliases and still handles arguments
*/ 


static int	builtin_alias_print(char *arg, t_aliaslst *aliaslst)
{
	char	*str_equal;
	int		arg_len;

	arg_len = ft_strlen(arg);
	while (aliaslst != NULL)
	{
		if (ft_strnequ(arg, aliaslst->var, arg_len) == true &&
			(aliaslst->var[arg_len] == '='))
		{
			str_equal = ft_strchr(aliaslst->var, '=');
			ft_printf("%.*s\'%s\'\n", str_equal - aliaslst->var + 1,
			aliaslst->var, str_equal + 1);
			return (FUNCT_SUCCESS);
		}
		aliaslst = aliaslst->next;
	}
	ft_eprintf("vsh: alias: %s: not found\n", arg);
	return (FUNCT_FAILURE);
}

static int	builtin_alias_args(char **args, int i, t_aliaslst **aliaslst)
{
	int		ret;
	char	*str_equal;

	ret = FUNCT_SUCCESS;
	while (args[i] != NULL && ret != FUNCT_ERROR)
	{
		str_equal = ft_strchr(args[i], '=');
		if (str_equal != NULL)
		{
			if (tools_is_valid_identifier(args[i]) == false ||
			(ft_strnequ(args[i], "alias", 5) && args[i][5] == '=') ||
			(ft_strnequ(args[i], "unalias", 7) && args[i][7] == '='))
			{
				ft_eprintf("vsh: alias: `%.*s': invalid alias name\n",
				str_equal - args[i], args[i]);
				ret = FUNCT_FAILURE;
			}
			else if (builtin_alias_set(args[i], aliaslst) == FUNCT_ERROR)
				ret = FUNCT_ERROR;
		}
		else if (builtin_alias_print(args[i], *aliaslst) == FUNCT_FAILURE)
			ret = FUNCT_FAILURE;
		i++;
	}
	return (ret);
}

static void	builtin_alias_printlst(t_aliaslst *aliaslst)
{
	char	*str_equal;

	while (aliaslst != NULL)
	{
		str_equal = ft_strchr(aliaslst->var, '=');
		ft_printf("%.*s\'%s\'\n", str_equal - aliaslst->var + 1,
		aliaslst->var, str_equal + 1);
		aliaslst = aliaslst->next;
	}
}

static int	builtin_alias_flag(char **args, int *flag, int *i)
{
	int j;

	while (args[*i] != NULL)
	{
		j = 1;
		if (args[*i][0] != '-' || args[*i][1] == '\0')
			return (FUNCT_SUCCESS);
		while (args[*i][j] != '\0')
		{
			if (args[*i][j] != 'p')
			{
				ft_eprintf("vsh: alias: -%c: invalid option\n", args[*i][j]);
				ft_eprintf("alias: usage: alias [-p] [name[=value] ... ]\n");
				return (FUNCT_FAILURE);
			}
			(*flag) |= ALIAS_FLAG_LP;
			j++;
		}
		(*i)++;
	}
	return (FUNCT_SUCCESS);
}

void		builtin_alias(char **args, t_aliaslst **aliaslst)
{
	int		flag;
	int		i;
	int		ret;

	i = 1;
	flag = 0;
	if (builtin_alias_flag(args, &flag, &i) == FUNCT_FAILURE)
	{
		g_state->exit_code = EXIT_WRONG_USE;
		return ;
	}
	if (args[i] == NULL || flag & ALIAS_FLAG_LP)
		builtin_alias_printlst(*aliaslst);
	if (args[i] != NULL)
	{
		ret = builtin_alias_args(args, i, aliaslst);
		if (ret == FUNCT_FAILURE)
			g_state->exit_code = EXIT_WRONG_USE;
		else if (ret == FUNCT_ERROR)
			g_state->exit_code = EXIT_FAILURE;
		else
			g_state->exit_code = EXIT_SUCCESS;
	}	
}
