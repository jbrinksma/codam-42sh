/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_quote_checker.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 07:47:19 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/28 12:22:36 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

char		shell_quote_checker_find_quote(char *line)
{
	int		i;
	char	quote;
	char	c;

	i = 0;
	quote = '\0';
	while (line[i] != '\0')
	{
		if (tools_is_char_escaped(line, i) == true)
		{
			i++;
			continue ;
		}
		c = line[i];
		if (quote == '\0' && (c == '\'' || c == '"'))
			quote = c;
		else if (quote != '\0' && c == quote)
			quote = '\0';
		i++;
	}
	return (quote);
}

/*
**	Right now there is no way of exiting the program through regular signals
**	if you don't supply the proper END_HERE input. Will need to be fixed through
**	some termcaps shit.
*/

int		shell_quote_checker(char **line, int *status)
{
	char	quote;
	char	*extra_line;

	quote = shell_quote_checker_find_quote(*line);
	while (quote != '\0')
	{
		if (quote == '\'')
			ft_printf("\nquote> ");
		else if (quote == '"')
			ft_printf("\ndquote> ");
		if (input_read(&extra_line, status) == FUNCT_ERROR)
		{
			ft_strdel(line);
			return (FUNCT_ERROR);
		}
		*line = ft_joinstrcstr_free_all(*line, '\n', extra_line);
		if (*line == NULL)
		{
			ft_eprintf("vsh: failed to allocate enough memory for commandline "
				"input\n");
			return (FUNCT_ERROR);
		}
		quote = shell_quote_checker_find_quote(*line);
	}
	return (FUNCT_SUCCESS);
}
