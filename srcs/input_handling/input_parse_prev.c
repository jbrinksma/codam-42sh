/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_prev.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:39:59 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/21 12:18:29 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void		parse_prev_move_word(unsigned *index, char **line)
{
	unsigned i;

	i = *index;
	if (*index == 0)
		return ;
	while (i > 0)
	{
		if (input_is_word_start(*line, i - 1, i) && i != *index)
			break ;
		i--;
	}
	ft_printf("\e[%dD", *index - i);
	*index = i;
}

int				input_parse_prev(char c, int *input_state,
	unsigned *index, char **line)
{
	if (((*input_state == INPUT_BRACE || *input_state == INPUT_D_BRACE) &&
		c == 'D') || c == '\2')
	{
		if (*input_state == 2)
		{
			if (*index > 0)
			{
				ft_printf("\e[D");
				*index -= 1;
			}
		}
		else
			parse_prev_move_word(index, line);
		*input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
