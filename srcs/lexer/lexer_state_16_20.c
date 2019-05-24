/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_16_20.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:14:21 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/24 11:36:14 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	state_ionum(t_scanner *scanner)
{
	if (ft_isdigit(CURRENT_CHAR))
		change_state(scanner, &state_ionum);
	else if (CURRENT_CHAR == '>' || CURRENT_CHAR == '<')
		scanner->tk_type = IO_NUMBER;
	else if (CURRENT_CHAR != '|' && CURRENT_CHAR != '>' && \
	CURRENT_CHAR != '<' && CURRENT_CHAR != '&' && CURRENT_CHAR != ';' && \
	CURRENT_CHAR != '\n' && !ft_isspace(CURRENT_CHAR) && CURRENT_CHAR != '\0')
		change_state(scanner, &state_word);
	else
		scanner->tk_type = WORD;
}

void	state_greatand(t_scanner *scanner)
{
	scanner->tk_type = GREATAND;
}

void	state_lessand(t_scanner *scanner)
{
	scanner->tk_type = LESSAND;
}

void	state_word_esc(t_scanner *scanner)
{
	if (CURRENT_CHAR != '\0')
		change_state(scanner, &state_word);
}
