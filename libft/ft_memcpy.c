/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 14:53:05 by omulder        #+#    #+#                */
/*   Updated: 2019/02/02 12:18:30 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	char		*ptrdst;
	char		*ptrsrc;
	size_t		i;

	ptrdst = (char*)dst;
	ptrsrc = (char*)src;
	i = 0;
	while (i < n)
	{
		ptrdst[i] = ptrsrc[i];
		i++;
	}
	return (dst);
}
