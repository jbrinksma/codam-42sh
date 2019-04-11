/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 16:03:08 by omulder        #+#    #+#                */
/*   Updated: 2019/02/02 12:29:09 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (((size_t)dst) - ((size_t)src) >= len)
		ft_memcpy(dst, (void*)src, len);
	else if (dst == src)
		return (dst);
	else
	{
		i = (int)(len - 1);
		while (i >= 0)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i--;
		}
	}
	return (dst);
}
