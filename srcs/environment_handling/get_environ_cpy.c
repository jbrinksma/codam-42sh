/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_environ_cpy.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 17:34:24 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 14:37:25 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Makes sure that the environ that is received has exactly one '=' in it.
**	Otherwise the var is not copied.
*/

int		check_for_single_equalsign(char *environ_arg)
{
	int index;
	int	found_equalsign;

	index = 0;
	found_equalsign = 0;
	while (environ_arg[index] != '\0')
	{
		if (environ_arg[index] == '=')
			found_equalsign++;
		index++;
	}
	if (found_equalsign == 1)
		return (FUNCT_SUCCESS);
	return (FUNCT_FAILURE);
}

/*
**	free any already allocated memory before returning NULL if any alloc
**	error occured.
*/

char	**free_and_return_null(char **vshenviron)
{
	ft_freearray(&vshenviron);
	return (NULL);
}

/*
**	Allocate, set, and return a pointer to a fresh copy of the
**	system's(???) environ.
*/

char		**get_environ_cpy(void)
{
	extern char **environ;
	char		**vshenviron;
	int			env_index;
	int			new_env_index;
	int			valid_var;

	vshenviron = (char**)malloc(sizeof(char*) * (ft_arraylen(environ) + 1));
	if (vshenviron == NULL)
		return (NULL);
	env_index = 0;
	new_env_index = 0;
	while (environ[env_index] != NULL)
	{
		valid_var = check_for_single_equalsign(environ[env_index]);
		if (valid_var)
		{
			vshenviron[env_index] = ft_strdup(environ[new_env_index]);
			if (vshenviron[env_index] == NULL)
				return (free_and_return_null(vshenviron));
			new_env_index++;
		}
		env_index++;
	}
	vshenviron[env_index] = NULL;
	return (vshenviron);
}
