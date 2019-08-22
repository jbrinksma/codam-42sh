/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_hash.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/18 13:09:06 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/22 11:56:49 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	set_flag(char *arg, int *flags)
{
	int i;

	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] == 'r')
			*flags |= HASH_LR;
		else
		{
			g_state->exit_code = EXIT_WRONG_USE;
			ft_eprintf(E_N_P_INV_OPT, "hash", arg[i]);
			ft_eprintf(U_HASH);
			return (FUNCT_FAILURE);
		}
		i++;
	}
	return (FUNCT_SUCCESS);
}

static int	check_flag(char **args, int *flag, int *argc)
{
	while (args[*argc] != NULL)
	{
		if (args[*argc][0] == '-')
		{
			if (args[*argc][1] == '\0')
				return (FUNCT_SUCCESS);
			if (set_flag(args[*argc], flag) == FUNCT_FAILURE)
				return (FUNCT_FAILURE);
		}
		else
			return (FUNCT_SUCCESS);
		(*argc)++;
	}
	return (FUNCT_SUCCESS);
}

static int	add_to_ht(char *cmd, t_vshdata *vshdata)
{
	int		ret;
	char	*bin_path;

	bin_path = NULL;
	ret = find_binary(cmd, vshdata->envlst, &bin_path);
	if (ret == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ret == FUNCT_FAILURE)
	{
		ft_eprintf(E_N_P_NOT_FOUND, "hash", cmd);
		return (FUNCT_FAILURE);
	}
	if (hash_ht_insert(vshdata, cmd, bin_path, HASH_NO_HIT) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

void		builtin_hash(char **args, t_vshdata *vshdata)
{
	int		flag;
	int		argc;

	flag = 0;
	argc = 1;
	if (args[argc] == NULL)
	{
		if (vshdata->ht_flag == HT_EMPTY)
			ft_printf("hash: hash table empty\n");
		else
			hash_print(vshdata->ht);
		return ;
	}
	if (check_flag(args, &flag, &argc) != FUNCT_SUCCESS)
		return ;
	if (flag & HASH_LR)
		hash_reset(vshdata);
	while (args[argc] != NULL)
	{
		if (add_to_ht(args[argc], vshdata) == FUNCT_ERROR)
			return ;
		argc++;
	}
}
