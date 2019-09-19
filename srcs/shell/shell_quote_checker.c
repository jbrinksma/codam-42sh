/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_quote_checker.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 07:47:19 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/17 17:30:17 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

char	shell_quote_checker_find_quote(char *line)
{
	int		i;
	char	quote;
	char	c;

	i = 0;
	quote = '\0';
	while (line[i] != '\0')
	{
		if (quote != '\'' && tools_is_char_escaped(line, i) == true)
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

int		shell_close_unclosed_quotes(t_vshdata *data)
{
	char	quote;
	char	*line_tmp;
	int		ret;

	quote = shell_quote_checker_find_quote(data->line->line);
	while (quote != '\0')
	{
		line_tmp = data->line->line;
		data->line->line = NULL;
		ft_putchar('\n');
		if (quote == '\'')
			shell_display_prompt(data, QUOTE_PROMPT);
		else if (quote == '"')
			shell_display_prompt(data, DQUOTE_PROMPT);
		ret = input_read(data);
		if (ret == FUNCT_ERROR || ret == NEW_PROMPT || ret == IR_EOF)
			return (ft_free_return(line_tmp, ret));
		data->line->line = ft_strjoinfree_all(line_tmp, data->line->line);
		if (data->line->line == NULL)
			return (err_ret(E_ALLOC_STR));
		quote = shell_quote_checker_find_quote(data->line->line);
	}
	return (FUNCT_SUCCESS);
}
