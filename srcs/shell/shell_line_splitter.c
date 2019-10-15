/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_line_splitter.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/19 17:44:26 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/01 12:45:46 by omulder       ########   odam.nl         */
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

static void	line_copy_increment(char *line, int *i, int *new_index)
{
	line[*new_index] = line[*i];
	(*new_index)++;
	(*i)++;
}

/*
**	shell_remove_escaped_newline removes escaped newlines
**	it also sets line_count
*/

static void	shell_remove_escaped_newline(char *line, int *line_count)
{
	char	quote;
	int		i;
	int		new_index;

	new_index = 0;
	quote = '\0';
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\\' && quote == '\0' && line[i + 1] == '\n')
		{
			i += 2;
			continue ;
		}
		else if (line[i] == '\\' && quote != '\'' && line[i + 1] != '\0')
			line_copy_increment(line, &i, &new_index);
		else if (line[i] == '\'' || line[i] == '\"')
			update_quote_status(line[i], &quote);
		else if (line[i] == '\n' && quote == '\0')
			(*line_count)++;
		line_copy_increment(line, &i, &new_index);
	}
	line_copy_increment(line, &i, &new_index);
	if (i > 0 && line[i - 1] != '\n')
		(*line_count)++;
}

char		**shell_line_splitter(t_vshdata *data)
{
	char	**lines;
	int		line_count;

	line_count = 0;
	shell_remove_escaped_newline(data->line->line, &line_count);
	lines = (char **)ft_memalloc(sizeof(char*) * (line_count + 1));
	if (lines == NULL || shell_split_line(data->line->line, lines)
		== FUNCT_ERROR)
	{
		err_void_exit(E_ALLOC_STR, EXIT_FAILURE);
		return (NULL);
	}
	ft_strdel(&data->line->line);
	return (lines);
}
