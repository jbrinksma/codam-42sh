/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freearray.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 01:48:39 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 14:51:05 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freearray(char ***array_p)
{
	int index;

	index = 0;
	if (*array_p)
	{
		while ((*array_p)[index] != NULL)
		{
			ft_strdel(&(*array_p)[index]);
			index++;
		}
		free(*array_p);
		*array_p = NULL;
	}
}
