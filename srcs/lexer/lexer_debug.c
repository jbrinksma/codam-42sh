/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_debug.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 16:06:49 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/09 15:44:56 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

#ifdef DEBUG

void	print_node(t_tokenlst *node)
{
	ft_printf("%-16s", parser_return_token_str(node->type));
	if (node->type == IO_NUMBER)
		ft_printf("%-16s", node->value);
	else if (node->type == WORD || node->type == ASSIGN)
		ft_printf("%-16s", node->value);
	else
		ft_printf("%-16s", parser_return_token_str(node->type));
	if (node->flags & T_FLAG_HASDOLLAR)
		ft_putstr("<has_dollar>");
	ft_putchar('\n');
}

void	print_token(t_scanner *scanner)
{
	char	*type;
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
	lexeme = ft_strndup(&(scanner->str[scanner->str_index - scanner->tk_len]),
		scanner->tk_len);
	ft_printf("\t%s\n", lexeme);
	ft_strdel(&lexeme);
}

#endif
