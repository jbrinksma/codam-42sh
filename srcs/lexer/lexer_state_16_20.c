/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_16_20.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:14:21 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/19 12:45:05 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	state_19(t_scanner *scanner)
{
	if (ft_isdigit(CURRENT_CHAR))
		change_state(scanner, &state_19);
	else if (CURRENT_CHAR == '>' || CURRENT_CHAR == '<')
		scanner->tk_type = IO_NUMBER;
	else if (CURRENT_CHAR != '|' && CURRENT_CHAR != '>' && \
	CURRENT_CHAR != '<' && CURRENT_CHAR != '&' && CURRENT_CHAR != ';' && \
	CURRENT_CHAR != '\n' && !ft_isspace(CURRENT_CHAR) && CURRENT_CHAR != '\0')
		change_state(scanner, &state_15);
	else
		scanner->tk_type = WORD;
}

void	state_18(t_scanner *scanner)
{
	scanner->tk_type = GREATAND;
}

void	state_17(t_scanner *scanner)
{
	scanner->tk_type = LESSAND;
}

void	state_16(t_scanner *scanner)
{
	if (CURRENT_CHAR != '\0')
		change_state(scanner, &state_15);
}
