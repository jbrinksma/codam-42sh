/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_joinstrcstr_free_all.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 18:32:41 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/29 18:32:57 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_joinstrcstr_free_all(char *s1, char c, char *s2)
{
	char	*str;

	str = ft_joinstrcstr(s1, c, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (str);
}
