/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_is_word_start.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/17 14:49:18 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/20 11:38:09 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			input_is_word_start(char *str, int i1, int i2)
{
	return (ft_isspace(str[i1]) &&
		ft_isspace(str[i2]) == 0 && ft_isprint(str[i2]));
}