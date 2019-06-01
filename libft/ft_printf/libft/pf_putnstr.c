/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_putnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 14:46:11 by omulder        #+#    #+#                */
/*   Updated: 2019/05/31 14:26:21 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	pf_putnstr(int fd, char const *s, size_t len)
{
	size_t i;

	i = 0;
	while (s[i] != '\0' && i < len)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
