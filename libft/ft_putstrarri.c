/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstrarri.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 15:45:53 by omulder        #+#    #+#                */
/*   Updated: 2019/02/01 11:56:09 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrarri(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != '\0')
	{
		ft_putnbr(i);
		ft_putstr(": ");
		ft_putendl(arr[i]);
		i++;
	}
}
