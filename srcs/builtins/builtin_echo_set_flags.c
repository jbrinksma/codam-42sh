/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo_set_flags.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/28 11:03:19 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/27 15:47:32 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	builtin_echo_merge_flags(char *flags, char tmp_flags)
{
	if (tmp_flags & ECHO_OPT_NL)
		*flags |= ECHO_OPT_NL;
	if (tmp_flags & ECHO_OPT_EL)
	{
		*flags |= ECHO_OPT_EL;
		*flags &= ~ECHO_OPT_EU;
	}
	if (tmp_flags & ECHO_OPT_EU)
	{
		*flags |= ECHO_OPT_EU;
		*flags &= ~ECHO_OPT_EL;
	}
}

static int	builtin_echo_validate_flag(char *tmp_flags, char flag)
{
	if (flag == 'E')
	{
		*tmp_flags |= ECHO_OPT_EU;
		*tmp_flags &= ~ECHO_OPT_EL;
	}
	else if (flag == 'e')
	{
		*tmp_flags |= ECHO_OPT_EL;
		*tmp_flags &= ~ECHO_OPT_EU;
	}
	else if (flag == 'n')
		*tmp_flags |= ECHO_OPT_NL;
	else
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

char		builtin_echo_set_flags(char **args, int *arg_i)
{
	char	tmp_flags;
	char	flags;
	int		i;

	flags = 0;
	while (args[*arg_i])
	{
		tmp_flags = 0;
		i = 0;
		if (args[*arg_i][0] != '-')
			return (flags);
		i++;
		while (args[*arg_i][i] != '\0')
		{
			if (builtin_echo_validate_flag(&tmp_flags, args[*arg_i][i]) == 0)
				return (flags);
			i++;
		}
		builtin_echo_merge_flags(&flags, tmp_flags);
		(*arg_i)++;
	}
	return (flags);
}
