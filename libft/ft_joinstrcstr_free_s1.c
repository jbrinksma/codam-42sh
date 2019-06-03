/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_joinstrcstr_free_s1.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 18:31:57 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/06/01 06:20:27 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_joinstrcstr_free_s1(char *s1, char c, char *s2)
{
	char	*str;

	str = ft_joinstrcstr(s1, c, s2);
	ft_strdel(&s1);
	return (str);
}
