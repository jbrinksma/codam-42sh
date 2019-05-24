/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_11_15.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:12:46 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/24 11:36:14 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	state_word(t_scanner *scanner)
{
	if (CURRENT_CHAR == '\\')
		change_state(scanner, &state_word_esc);
	else if (CURRENT_CHAR == '"')
		change_state(scanner, &state_dquote);
	else if (CURRENT_CHAR == '\'')
		change_state(scanner, &state_squote);
	else if (ft_isdigit(CURRENT_CHAR) && scanner->tk_len == 0)
		change_state(scanner, &state_ionum);
	else if (CURRENT_CHAR != '|' && CURRENT_CHAR != '>' && \
	CURRENT_CHAR != '<' && CURRENT_CHAR != '&' && CURRENT_CHAR != ';' && \
	CURRENT_CHAR != '\n' && !ft_isspace(CURRENT_CHAR) && CURRENT_CHAR != '\0')
		change_state(scanner, &state_word);
	else
		scanner->tk_type = WORD;
}

void	state_dquote_esc(t_scanner *scanner)
{
	if (CURRENT_CHAR != '\0')
		change_state(scanner, &state_dquote);
}

void	state_dquote(t_scanner *scanner)
{
	if (CURRENT_CHAR == '\\')
		change_state(scanner, &state_dquote_esc);
	else if (CURRENT_CHAR == '"')
		change_state(scanner, &state_word);
	else if (CURRENT_CHAR != '\\' && CURRENT_CHAR != '"' && \
	CURRENT_CHAR != '\0')
		change_state(scanner, &state_dquote);
}

void	state_squote(t_scanner *scanner)
{
	if (CURRENT_CHAR == '\'')
		change_state(scanner, &state_word);
	else if (CURRENT_CHAR != '\'' && CURRENT_CHAR != '\0')
		change_state(scanner, &state_squote);
}

void	state_newline(t_scanner *scanner)
{
	scanner->tk_type = NEWLINE;
}
