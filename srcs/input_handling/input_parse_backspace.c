/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_backspace.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:43:07 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/20 10:23:40 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

# define INPUT_BACKSPACE	127

int				input_parse_backspace(char c, unsigned *index, char **line)
{
	unsigned len;

	if (c == INPUT_BACKSPACE)
	{
		if (*index > 0)
		{
			input_clear_char_at(line, *index - 1);
			ft_printf("\e[D%s \e[D", *line + *index - 1);
			len = ft_strlen(&(*line)[*index - 1]);
			if (len > 1)
				ft_printf("\e[%dD", len);
			(*index)--;
		}
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
