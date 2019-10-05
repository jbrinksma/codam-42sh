/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_scanner.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 11:12:49 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/03 17:00:38 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	init_scanner(char *str, t_scanner *scanner)
{
	ft_bzero(scanner, sizeof(t_scanner));
	scanner->str = str;
}

static void	reset_scanner(t_scanner *scanner)
{
	scanner->tk_len = 0;
	scanner->flags = 0;
	scanner->tk_type = ERROR;
}

/*
**	Token-related scanner values are read and used to generate the token.
**	The token is then added to token_lst.
*/

static int	scan_to_lst(t_tokenlst *token_lst, t_scanner *scanner)
{
	t_tokens	type;
	char		*value;
	int			flags;
	int			tk_start;

	tk_start = scanner->str_index - scanner->tk_len;
	if (tk_start < 0)
		return (FUNCT_ERROR);
	type = scanner->tk_type;
	flags = scanner->flags;
	value = NULL;
	if (type == WORD || type == ASSIGN || type == IO_NUMBER)
	{
		value = ft_strndup(&(scanner->str[tk_start]), scanner->tk_len);
		if (value == NULL)
			return (FUNCT_ERROR);
	}
	if (lexer_tokenlstaddback(&token_lst, type, value, flags) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

/*
**	A scanner struct is used to go over the command line. The scanner keeps
**	track of the index on line, as well as a pointer to line itself. The scanner
**	struct also keeps track of the current token length, the current
**	token type, and its optional flags.
**
**	When the scanner comes to the end of a specific token, its values
**	are used to generate and save the token. The token-specific values of the
**	scanner are then reset.
**
**	This process is repeated until the whole line has been lexed, or an
**	error occurs.
*/

int			lexer_scanner(char *line, t_tokenlst *token_lst)
{
	t_scanner scanner;

	init_scanner(line, &scanner);
	while (ft_isblank(SCANNER_CHAR) == true)
		(scanner.str_index)++;
	while (SCANNER_CHAR != '\0')
	{
		lexer_state_start(&scanner);
		if (scan_to_lst(token_lst, &scanner) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		reset_scanner(&scanner);
		while (ft_isblank(SCANNER_CHAR) == true)
			(scanner.str_index)++;
	}
	return (FUNCT_SUCCESS);
}
