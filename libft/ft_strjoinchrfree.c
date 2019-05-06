/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoinchrfree.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/06 14:12:14 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/06 15:28:39 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_strjoinchrfree(char *s1, char c, int i)
{
	char	*str;

	str = ft_strjoinchr(s1, c);
	if (i == 1)
		ft_strdel(&s1);
	return (str);
}
