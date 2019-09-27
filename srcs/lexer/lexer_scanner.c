/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_scanner.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 11:12:49 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/27 14:52:45 by tde-jong      ########   odam.nl         */
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
