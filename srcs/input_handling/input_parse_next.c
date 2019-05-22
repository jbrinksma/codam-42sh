/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_next.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:41:00 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/22 11:57:08 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	parse_next_move_word(unsigned *index, char **line)
{
	unsigned i;

	i = *index + 1;
	if (*index == ft_strlen(*line))
		return ;
	while ((*line)[i])
	{
		if (input_is_word_start(*line, i - 1, i))
			break ;
		i++;
	}
	ft_printf("%.*s", i - *index, *line + *index);
	*index = i;
}

int			input_parse_next(char c, int *input_state,
	unsigned *index, char **line)
{
	if (((*input_state == INPUT_BRACE || *input_state == INPUT_D_BRACE) &&
		c == 'C') || c == '\6')
	{
		if (*input_state == INPUT_BRACE)
		{
			if (*index < ft_strlen(*line))
			{
				ft_putchar((*line)[*index]);
				*index += 1;
			}
		}
		else
			parse_next_move_word(index, line);
		*input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
