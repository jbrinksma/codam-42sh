/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_is_char_escaped.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/27 16:52:15 by omulder        #+#    #+#                */
/*   Updated: 2019/06/02 08:50:50 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <stdbool.h>

/*
**	Checks the given string with it's given index, and looks back to check if
**	the line[cur_index] is escaped.
**
**	Returns true if escaped, false if not escaped.
*/

bool	tools_is_char_escaped(char *line, int i)
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
		return (true);
	return (false);
}
