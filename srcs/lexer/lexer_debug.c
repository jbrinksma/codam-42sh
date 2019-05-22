/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_debug.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 16:06:49 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/21 21:14:57 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

#ifdef DEBUG

void	put_token(t_tokenlst *node)
{
	char	*token;

	if (node->type == START)
		token = "START";
	else if (node->type == ASSIGN)
		token = "ASSIGN";
	else if (node->type == WORD)
		token = "WORD";
	else if (node->type == IO_NUMBER)
		token = "IO_NUM";
	else if (node->type == AND_IF)
		token = "AND_IF";
	else if (node->type == OR_IF)
		token = "OR_IF";
	else if (node->type == DLESS)
		token = "DLESS";
	else if (node->type == DGREAT)
		token = "DGREAT";
	else if (node->type == SLESS)
		token = "SLESS";
	else if (node->type == SGREAT)
		token = "SGREAT";
	else if (node->type == LESSAND)
		token = "LESSAND";
	else if (node->type == GREATAND)
		token = "GREATAND";
	else if (node->type == BG)
		token = "BG";
	else if (node->type == PIPE)
		token = "PIPE";
	else if (node->type == SEMICOL)
		token = "SEMICOL";
	else if (node->type == END)
		token = "END";
	else
		token = "ERROR";

	ft_printf("%-16s", token);
}

void	print_node(t_tokenlst *node)
{
	put_token(node);
	if (node->type == IO_NUMBER)
		ft_putnbr(ft_atoi(node->value));
	else if (node->type == WORD || node->type == ASSIGN)
		ft_putstr(node->value);
	else
		put_token(node);
	if (node->type != END)
		ft_putchar('\n');
}

void	print_token(t_scanner *scanner)
{
	char			*type;
	char	*lexeme;

	if (scanner->tk_type == WORD)
		type = "WORD";
	else if (scanner->tk_type == PIPE)
		type = "PIPE";
	else if (scanner->tk_type == SLESS)
		type = "SLESS";
	else if (scanner->tk_type == SGREAT)
		type = "SGREAT";
	else if (scanner->tk_type == DLESS)
		type = "DLESS";
	else if (scanner->tk_type == DGREAT)
		type = "DGREAT";
	else if (scanner->tk_type == BG)
		type = "BG";
	else if (scanner->tk_type == SEMICOL)
		type = "SEMICOLON";
	else if (scanner->tk_type == AND_IF)
		type = "AND_IF";
	else if (scanner->tk_type == OR_IF)
		type = "OR_IF";
	else if (scanner->tk_type == NEWLINE)
		type = "NEWLINE";
	else
		type = "UNKNOWN";
	ft_printf("\n%s (%i): ", type, scanner->tk_len);
	lexeme = ft_strndup(&(scanner->str[scanner->str_index - scanner->tk_len]), scanner->tk_len);
	ft_printf("\t%s\n", lexeme);
	ft_strdel(&lexeme);
}

#endif
