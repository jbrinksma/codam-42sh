/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_11_15.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:12:46 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/19 12:54:59 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	state_15(t_scanner *scanner)
{
	if (CURRENT_CHAR == '\\')
		change_state(scanner, &state_16);
	else if (CURRENT_CHAR == '"')
		change_state(scanner, &state_13);
	else if (CURRENT_CHAR == '\'')
		change_state(scanner, &state_12);
	else if (ft_isdigit(CURRENT_CHAR) && scanner->tk_len == 0)
		change_state(scanner, &state_19);
	else if (CURRENT_CHAR != '|' && CURRENT_CHAR != '>' && \
	CURRENT_CHAR != '<' && CURRENT_CHAR != '&' && CURRENT_CHAR != ';' && \
	CURRENT_CHAR != '\n' && !ft_isspace(CURRENT_CHAR) && CURRENT_CHAR != '\0')
		change_state(scanner, &state_15);
	else
		scanner->tk_type = WORD;
}

void	state_14(t_scanner *scanner)
{
	if (CURRENT_CHAR != '\0')
		change_state(scanner, &state_13);
}

void	state_13(t_scanner *scanner)
{
	if (CURRENT_CHAR == '\\')
		change_state(scanner, &state_14);
	else if (CURRENT_CHAR == '"')
		change_state(scanner, &state_15);
	else if (CURRENT_CHAR != '\\' && CURRENT_CHAR != '"' && \
	CURRENT_CHAR != '\0')
		change_state(scanner, &state_13);
}

void	state_12(t_scanner *scanner)
{
	if (CURRENT_CHAR == '\'')
		change_state(scanner, &state_15);
	else if (CURRENT_CHAR != '\'' && CURRENT_CHAR != '\0')
		change_state(scanner, &state_12);
}

void	state_11(t_scanner *scanner)
{
	scanner->tk_type = NEWLINE;
}
