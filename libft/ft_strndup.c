/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 13:26:21 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/27 16:59:10 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*cpy;

	cpy = ft_strnew(n);
	if (cpy == NULL)
		return (NULL);
	ft_strncpy(cpy, s1, n);
	return (cpy);
}
