/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freearray.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 01:48:39 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/19 19:06:24 by jbrinksm      ########   odam.nl         */
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
	}
}
