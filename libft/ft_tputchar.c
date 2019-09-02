/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tputchar.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:33:54 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/29 14:53:47 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int ft_tputchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return (1);
}
