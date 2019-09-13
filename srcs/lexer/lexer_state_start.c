/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_start.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:10:51 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/10 16:20:13 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	lexer_state_semicol(t_scanner *scanner)
{
	scanner->tk_type = SEMICOL;
}

void	lexer_state_andif(t_scanner *scanner)
{
	scanner->tk_type = AND_IF;
}

void	lexer_state_orif(t_scanner *scanner)
{
	scanner->tk_type = OR_IF;
}

void	lexer_set_flags(t_scanner *scanner, char c)
{
	if (tool_is_special(c) == true)
		scanner->flags |= T_FLAG_HASSPECIAL;
	if (c == '"')
		scanner->flags ^= T_STATE_DQUOTE;
	if (c == '\'')
		scanner->flags ^= T_STATE_SQUOTE;
}

void	lexer_state_start(t_scanner *scanner)
{
	lexer_set_flags(scanner, CURRENT_CHAR);
	if (CURRENT_CHAR == '|')
		lexer_change_state(scanner, &lexer_state_pipe);
	else if (CURRENT_CHAR == '>')
		lexer_change_state(scanner, &lexer_state_sgreat);
	else if (CURRENT_CHAR == '<')
		lexer_change_state(scanner, &lexer_state_sless);
	else if (CURRENT_CHAR == '&')
		lexer_change_state(scanner, &lexer_state_bg);
	else if (CURRENT_CHAR == ';')
		lexer_change_state(scanner, &lexer_state_semicol);
	else if (CURRENT_CHAR == '\\')
		lexer_change_state(scanner, &lexer_state_word_esc);
	else if (CURRENT_CHAR == '\n')
		lexer_change_state(scanner, &lexer_state_newline);
	else if (ft_isdigit(CURRENT_CHAR))
		lexer_change_state(scanner, &lexer_state_ionum);
	else
		lexer_change_state(scanner, &lexer_state_word);
}
