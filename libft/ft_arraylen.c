/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arraylen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 17:38:52 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/19 19:06:21 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arraylen(char **array)
{
	int i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}
