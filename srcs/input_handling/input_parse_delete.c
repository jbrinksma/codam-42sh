/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_delete.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:44:53 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/17 14:46:09 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int				input_parse_delete(char c, int *input_state,
	unsigned *index, char **line)
{
	unsigned i;

	if (*input_state == INPUT_THREE && c == '~')
	{
		if (*index < ft_strlen(*line))
		{
			i = 0;
			input_clear_char_at(line, *index);
			ft_printf("%s ", *line + *index);
			ft_printf("\e[%dD", ft_strlen(*line + *index) + 1);
		}
		*input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
