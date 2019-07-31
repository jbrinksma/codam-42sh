/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_d.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:46:55 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/31 13:00:06 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int	input_parse_ctrl_d(t_inputdata *data, t_vshdata *vshdata, char **line)
{
	unsigned	len;

	if (data->c == '\4')
	{
		len = ft_strlen(*line);
		if (len == 0)
			builtin_exit(NULL, vshdata);
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
