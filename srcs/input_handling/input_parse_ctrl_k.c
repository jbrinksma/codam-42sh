/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_k.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:48:04 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/15 16:31:45 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int	input_parse_ctrl_k(t_inputdata *data, char **line)
{
	unsigned i;

	if (data->c == '\v')
	{
		if (data->index < ft_strlen(*line))
		{
			i = (data->index);
			while ((*line)[i])
			{
				ft_putchar(' ');
				(*line)[i] = '\0';
				i++;
			}
			ft_printf("\e[%dD", i - data->index);
		}
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
