/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_find_state.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/12 17:12:17 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/05 15:45:03 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Auto find state loops back from index to find the state
**	The state can be a command, variable or file path
*/

static bool	is_cmd_seperator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '\n');
}

static int	find_state_before_whitespace(char *line, int i)
{
	while (i >= 0)
	{
		if (line[i] != ' ' && line[i] != '\t')
			break ;
		i--;
	}
	if (i < 0 || is_cmd_seperator(line[i]) == true)
		return (STATE_CMD);
	return (STATE_FILE);
}

int			auto_find_state(char *line, ssize_t i)
{
	if (i == 0)
		return (STATE_CMD);
	i--;
	while (i >= 0)
	{
		if (tools_is_valid_name_char(line[i]) == false || line[i] == '$')
			break ;
		i--;
	}
	if (i < 0 || is_cmd_seperator(line[i]) == true)
		return (STATE_CMD);
	if (line[i] == ' ' || line[i] == '\t')
		return (find_state_before_whitespace(line, i));
	if (line[i] == '$' || (i > 0 && line[i] == '{' && line[i - 1] == '$'))
		return (STATE_VAR);
	return (STATE_FILE);
}
