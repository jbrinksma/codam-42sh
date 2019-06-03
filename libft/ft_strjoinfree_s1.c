/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoinfree_s1.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/16 20:15:07 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/16 20:20:01 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree_s1(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	ft_strdel(&s1);
	return (str);
}
