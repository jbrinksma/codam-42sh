/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_lexer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:57:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/05 12:53:45 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	NOTE: This code is nowhere near from perfect and any help and/or suggestions
**	are appreciated.
*/

/*
**	IMPORTANT: add check for more than one subsequent ';' command seperator.
**	It's not allowed.
*/

#include "vsh.h"

/*
**	Useful function to check wether a character is ';' and also outside
**	of any quotes or escape char. (the quote argument is used to check if
**	you're currently in a quote, see update_quote_char).
*/

int		is_uninhibited_semicolon(char *str, int i, char quote)
{
	if (str[i] == ';' && quote == '\0')
	{
		if (is_char_escaped(str, i) == true)
			return (false);
		return (true);
	}
	return (false);
}

/*
**	Useful function to check wether a character is ' ' || '\t' and also outside
**	of any quotes or escape char. (the quote argument is used to check if
**	you're currently in a quote, see update_quote_char).
*/

int		is_uninhibited_blank(char *str, int i, char quote)
{
	if ((str[i] == ' ' || str[i] == '\t') && quote == '\0')
	{
		if (is_char_escaped(str, i) == true)
			return (false);
		return (true);
	}
	return (false);
}

/*
**	The goal of this function is to simple seperate the input line into
**	a command table (cmd_tab). Firstly the commands are seperated by ';' chars,
**	then the command lines themselves are seperated by '\t' and ' ' chars.
**	Naturally, we are keeping track of quotes and escape chars along the way.
**	The uninhibited(!) ';', '\'', '"', \t', and ' ' chars are removed, as are
**	the escape chars that escaped one of those chars, since they no longer
**	serve a special meaning in the parser after this.
**	The resulting cmd_tab is structured as follows:
**
**	t_list* cmd_tab----> content(t_list* args)----------> content(char* of arg1)
**			|								|
**			|							next|
**			|		(1st command)		item|-----------> content(char* of arg2)
**			|								|
**			|							next|
**			|							item|-----------> content(char* of arg3)
**			|								|
**			|							next|
**			|							item= NULL
**		next|
**		item|----------> content(t_list* args)----------> content(char* of arg1)
**			|								|
**			|							next|
**			|		(2nd command)		item|-----------> content(char* of arg2)
**			|								|
**			|							next|
**			|							item|-----------> content(char* of arg3)
**			|								|
**			|							next|
**			|							item= NULL
**		next|
**		item|----------> content(t_list* args)----------> content(char* of arg1)
**			|								|
**			|							next|
**			|		(3rd command)		item|-----------> content(char* of arg2)
**			|								|
**		   ...							   ...
*/

int		parser_lexer(char *line, t_list **cmd_tab)
{
	t_list		*cmdstr_lst;
	t_list		*probe;
	t_list		*args;

	cmdstr_lst = parser_split_line_to_commands(line);
	parser_rem_esc_char_semicolons(cmdstr_lst);
	probe = cmdstr_lst;
	while (probe != NULL)
	{
		if (probe->content != NULL)
		{
			args = parser_split_command_to_args(probe->content);
			parser_remove_quotes(args);
			parser_rem_esc_char_quotes(args);
			parser_rem_esc_char_blanks(args);
			add_lst_to_lst(args, cmd_tab);
		}
		probe = probe->next;
	}
	return (FUNCT_SUCCESS);
}
