/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_get_environ_cpy.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 13:43:01 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 15:10:25 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		test_check_for_single_equalsign(void)
{
	if (check_for_single_equalsign("ENV=value") != FUNCT_SUCCESS)
		return (FUNCT_FAILURE);
	if (check_for_single_equalsign("ENVvalue") != FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	if (check_for_single_equalsign("ENV=value=") != FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	if (check_for_single_equalsign("") != FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

int		test_free_and_return_null(void)
{
	char	**testenv;

	testenv = (char**)ft_memalloc(sizeof(char*) * 3);
	if (testenv == NULL)
		return (FUNCT_FAILURE);
	testenv[0] = ft_strdup("test");
		if (testenv[0] == NULL)
			return (FUNCT_FAILURE);
	testenv[1] = ft_strdup("test");
		if (testenv[1] == NULL)
			return (FUNCT_FAILURE);
	if (free_and_return_null(testenv) != NULL)
		return (FUNCT_FAILURE);
	if (testenv[0] != NULL)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

int		test_get_environ_cpy(void)
{
	extern char **environ;
	char		**vshenviron;
	int			index;

	vshenviron = get_environ_cpy();
	index = 0;
	if (vshenviron == NULL)
		return (FUNCT_FAILURE);
	while (vshenviron[index] != NULL && environ[index] != NULL)
	{
		if (ft_strcmp(vshenviron[index], environ[index]))
		{
			ft_freearray(&vshenviron);
			return (FUNCT_FAILURE);
		}
		index++;
	}
	if (vshenviron[index] != NULL || environ[index] != NULL)
	{
		ft_freearray(&vshenviron);
		return (FUNCT_FAILURE);
	}
	ft_freearray(&vshenviron);
	return (FUNCT_SUCCESS);
}
