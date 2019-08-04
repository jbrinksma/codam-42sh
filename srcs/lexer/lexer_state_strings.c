/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_strings.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:12:00 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/04 12:59:56 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	lexer_state_ionum(t_scanner *scanner)
{
	if (ft_isdigit(CURRENT_CHAR) == true)
		lexer_change_state(scanner, &lexer_state_ionum);
	else if (CURRENT_CHAR == '>' || CURRENT_CHAR == '<')
		scanner->tk_type = IO_NUMBER;
	else
		lexer_state_word(scanner);
}

void	lexer_state_word_esc(t_scanner *scanner)
{
	if (CURRENT_CHAR != '\0')
		lexer_change_state(scanner, &lexer_state_word);
}

void	lexer_state_word(t_scanner *scanner)
{
	if (tool_is_special(CURRENT_CHAR) == true)
		scanner->flags |= T_FLAG_HASSPECIAL;
	if (CURRENT_CHAR == '=' && scanner->str[0] != '='
		&& (scanner->flags & T_FLAG_HASSPECIAL) == false)
		scanner->flags |= T_FLAG_ISASSIGN;
	if (CURRENT_CHAR == '"' && (scanner->flags & T_STATE_SQUOTE) == false)
		scanner->flags ^= T_STATE_DQUOTE;
	if (CURRENT_CHAR == '\'' && (scanner->flags & T_STATE_DQUOTE) == false)
		scanner->flags ^= T_STATE_SQUOTE;
	if (CURRENT_CHAR == '\\' && (scanner->flags & T_STATE_SQUOTE) == false)
		lexer_change_state(scanner, &lexer_state_word_esc);
	else if (lexer_is_shellspec(CURRENT_CHAR) == false &&
			ft_isspace(CURRENT_CHAR) == false && CURRENT_CHAR != '\0')
		lexer_change_state(scanner, &lexer_state_word);
	else if ((scanner->flags & T_STATE_DQUOTE ||
			scanner->flags & T_STATE_SQUOTE) && CURRENT_CHAR != '\0')
		lexer_change_state(scanner, &lexer_state_word);
	else if (scanner->flags & T_FLAG_ISASSIGN)
		scanner->tk_type = ASSIGN;
	else
		scanner->tk_type = WORD;
}
