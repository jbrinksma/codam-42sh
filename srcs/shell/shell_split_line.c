/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_split_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 20:05:50 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/08 17:35:50 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	update_quote_status(char c, char *quote)
{
	if (*quote == '\0')
		*quote = c;
	else if (c == *quote)
		*quote = '\0';
}

static int	shell_add_line(char *line, int i, char **lines, int reset)
{
	static int line_index;
	static int line_count;

	if (reset == true)
	{
		line_index = 0;
		line_count = 0;
		return (FUNCT_SUCCESS);
	}
	lines[line_count] = ft_strsub(line, line_index, i - line_index);
	if (lines[line_count] == NULL)
		return (FUNCT_ERROR);
	line_index = i + 1;
	line_count++;
	return (FUNCT_SUCCESS);
}

/*
**	shell_split_line copies substrings (a completed command) of line to lines
**  The shell_add_line(NULL, 0, NULL, true); is just to clear the static vars
**  It's a bit hacky but hey it works.
*/

int			shell_split_line(char *line, char **lines)
{
	char	quote;
	int		i;

	quote = '\0';
	i = 0;
	shell_add_line(NULL, 0, NULL, true);
	while (line[i] != '\0')
	{
		if (line[i] == '\\' && quote != '\'' && line[i + 1] != '\0')
			i++;
		else if (line[i] == '\'' || line[i] == '\"')
			update_quote_status(line[i], &quote);
		else if (line[i] == '\n' && quote == '\0' &&
			shell_add_line(line, i, lines, false) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		i++;
	}
	if (i > 0 && line[i - 1] != '\n' &&
		shell_add_line(line, i, lines, false) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
