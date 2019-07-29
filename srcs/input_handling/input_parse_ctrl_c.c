/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_c.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/29 13:54:20 by tde-jong       #+#    #+#                */
/*   Updated: 2019/07/29 17:26:09 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int	input_parse_ctrl_c(t_inputdata *data)
{
	if (data->c == '\3')
	{
		ft_putchar('\n');
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
