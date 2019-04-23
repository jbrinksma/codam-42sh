/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstrarr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 15:43:03 by omulder        #+#    #+#                */
/*   Updated: 2019/04/23 19:36:41 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrarr(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putendl(arr[i]);
		i++;
	}
}
