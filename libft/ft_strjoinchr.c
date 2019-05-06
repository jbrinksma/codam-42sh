/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoinchr.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/06 14:10:46 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/06 14:11:47 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_strjoinchr(char const *s1, char c)
{
	char	*join;

	if (s1 == NULL)
		return (NULL);
	join = ft_strnew(ft_strlen(s1) + 1);
	if (join == NULL)
		return (NULL);
	ft_strcpy(join, s1);
    join[ft_strlen(s1)] = c;
	return (join);
}
