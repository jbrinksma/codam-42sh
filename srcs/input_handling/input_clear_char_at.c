/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_clear_char_at.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/30 10:30:47 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/30 10:38:06 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		input_clear_char_at(char **line, unsigned index)
{
	unsigned i;

	i = index;
	while ((*line)[i])
	{
		(*line)[i] = (*line)[i + 1];
		i++;
	}
}
