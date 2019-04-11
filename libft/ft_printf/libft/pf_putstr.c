/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_putstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 12:05:27 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:32:01 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putstr(int fd, char const *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
