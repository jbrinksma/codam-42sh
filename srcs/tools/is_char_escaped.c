/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_char_escaped.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/23 13:59:19 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/16 20:43:54 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Checks the given string with it's given index, and looks back to check if
**	the line[cur_index] is escaped.
**
**	Returns FUNCT_SUCCESS if escaped, FUNCT_FAILURE if not escaped.
*/

int	is_char_escaped(char *line, int i)
{
	int i_tmp;
	int	escape_count;

	i_tmp = i - 1;
	escape_count = 0;
	while (i_tmp >= 0 && line[i_tmp] == '\\')
	{
		escape_count++;
		i_tmp--;
	}
	if (escape_count % 2 != 0)
		return (FUNCT_SUCCESS);
	return (FUNCT_FAILURE);
}
