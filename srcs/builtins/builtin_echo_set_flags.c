/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo_set_flags.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/28 11:03:19 by mavan-he       #+#    #+#                */
/*   Updated: 2019/04/28 17:10:45 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	echo_merge_flags(char *flags, char tmp_flags)
{
	if (tmp_flags & OPT_N)
		*flags |= OPT_N;
	if (tmp_flags & OPT_E)
	{
		*flags |= OPT_E;
		*flags &= ~OPT_CE;
	}
	if (tmp_flags & OPT_CE)
	{
		*flags |= OPT_CE;
		*flags &= ~OPT_E;
	}
}

static int	echo_validate_flag(char *tmp_flags, char c)
{
	if (c == 'E')
	{
		*tmp_flags |= OPT_CE;
		*tmp_flags &= ~OPT_E;
	}
	else if (c == 'e')
	{
		*tmp_flags |= OPT_E;
		*tmp_flags &= ~OPT_CE;
	}
	else if (c == 'n')
		*tmp_flags |= OPT_N;
	else
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

char		echo_set_flags(char **args, int *arg_i)
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
			if (echo_validate_flag(&tmp_flags, args[*arg_i][i]) == 0)
				return (flags);
			i++;
		}
		echo_merge_flags(&flags, tmp_flags);
		(*arg_i)++;
	}
	return (flags);
}
