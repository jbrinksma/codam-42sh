/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_char_escaped.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/23 13:59:19 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 19:12:25 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Checks the given string with it's given index, and looks back to check if
**	the line[cur_index] is escaped.
**
**	Returns FUNCT_SUCCESS if escaped, FUNCT_FAILURE if not escaped.
*/

int	is_char_escaped(char *line, int cur_index)
{
	int index;
	int	total_escape_chars;

	index = cur_index - 1;
	if (index < 0 || index > (int)ft_strlen(line))
		return (FUNCT_FAILURE);
	if (line[index] == '\\')
	{
		total_escape_chars = 0;
		while (line[index] == '\\' && index >= 0)
		{
			total_escape_chars++;
			index--;
		}
		if (total_escape_chars % 2 == 1)
			return (FUNCT_SUCCESS);
		else
			return (FUNCT_FAILURE);
	}
	return (FUNCT_FAILURE);
}
