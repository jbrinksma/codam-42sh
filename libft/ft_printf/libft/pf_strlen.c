/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 13:28:01 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:29:52 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	pf_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
