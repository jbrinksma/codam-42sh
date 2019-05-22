/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_end.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:39:04 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/22 11:56:51 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int	input_parse_end(char c, int *input_state, unsigned *index, char **line)
{
	if ((*input_state == INPUT_BRACE && c == 'F') || c == '\5')
	{
		ft_printf("%s", *line + *index);
		*index = ft_strlen(*line);
		*input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
