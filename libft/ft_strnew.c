/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 10:59:30 by omulder        #+#    #+#                */
/*   Updated: 2019/02/02 12:26:09 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*mem;
	size_t	i;

	mem = (char*)malloc(sizeof(char) * (size + 1));
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < (size + 1))
	{
		mem[i] = '\0';
		i++;
	}
	return (mem);
}
