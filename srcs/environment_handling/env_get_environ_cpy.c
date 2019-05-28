/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_get_environ_cpy.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 17:34:24 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/27 15:51:51 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	free any already allocated memory before returning NULL if any alloc
**	error occured.
*/

char	**env_free_and_return_null(char ***vshenviron)
{
	ft_freearray(vshenviron);
	return (NULL);
}

/*
**	Allocate, set, and return a pointer to a fresh copy of the
**	system's(???) environ.
*/

char	**env_get_environ_cpy(void)
{
	extern char **environ;
	char		**vshenviron;
	int			env_index;

	vshenviron = (char**)ft_memalloc(sizeof(char*) * \
	(ft_arraylen(environ) + 1));
	if (vshenviron == NULL)
		return (NULL);
	env_index = 0;
	while (environ[env_index] != NULL)
	{
		vshenviron[env_index] = ft_strdup(environ[env_index]);
		if (vshenviron[env_index] == NULL)
			return (env_free_and_return_null(&vshenviron));
		env_index++;
	}
	vshenviron[env_index] = NULL;
	return (vshenviron);
}
