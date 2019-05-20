/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_split_line_to_commands.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/23 14:03:51 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/05 12:51:14 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	NOTE: This code is nowhere near from perfect and any help and/or suggestions
**	are appreciated.
*/

#include "vsh.h"

/*
**	Returns the amount of characters before reaching a '\0' char or a
**	uninhibited ';' char.
*/

int		parser_strlen_cmd(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	update_quote_status(line, i, &quote);
	while (line[i] != '\0' && is_uninhibited_semicolon(line, i, quote) != true)
	{
		i++;
		update_quote_status(line, i, &quote);
	}
	return (i);
}

/*
**	Splits the line input into a list of seperate commands (which are delimited
**	by uninhibited ';' chars) into a string form.
*/

t_list	*parser_split_line_to_commands(char *line)
{
	t_list	*command_lst;
	char	*command;
	int		i;
	int		len;

	command_lst = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		while (ft_isblank(line[i]) == true)
			i++;
		len = parser_strlen_cmd(&line[i]);
		if (len > 0)
		{
			command = ft_strndup(&line[i], len);
			add_str_to_lst(command, &command_lst);
			ft_strdel(&command);
			i += len;
		}
		else
			i++;
	}
	return (command_lst);
}
