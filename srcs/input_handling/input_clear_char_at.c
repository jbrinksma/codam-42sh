/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_clear_char_at.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/30 10:30:47 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/06 10:28:07 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Removes the character at index from the command line internally.
*/

void		input_clear_char_at(char **line, unsigned index)
{
	while ((*line)[index])
	{
		(*line)[index] = (*line)[index + 1];
		index++;
	}
}
