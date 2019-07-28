/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_d.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:46:55 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/15 16:31:56 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int	input_parse_ctrl_d(t_inputdata *data, char **line)
{
	unsigned	len;

	if (data->c == '\4')
	{
		len = ft_strlen(*line);
		if (len == 0)
			exit(0);
		if (data->index < len)
		{
			input_clear_char_at(line, data->index);
			ft_printf("%s ", *line + data->index);
			ft_printf("\e[%dD", ft_strlen(*line + data->index) + 1);
		}
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
