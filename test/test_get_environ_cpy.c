/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_get_environ_cpy.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 13:43:01 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/19 20:34:06 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

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
