/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_1_5.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:10:51 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/19 12:45:45 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	state_5(t_scanner *scanner)
{
	scanner->tk_type = DGREAT;
}

void	state_4(t_scanner *scanner)
{
	if (CURRENT_CHAR == '>')
		change_state(scanner, &state_5);
	else if (CURRENT_CHAR == '&')
		change_state(scanner, &state_18);
	else
		scanner->tk_type = SGREAT;
}

void	state_3(t_scanner *scanner)
{
	scanner->tk_type = OR_IF;
}

void	state_2(t_scanner *scanner)
{
	if (CURRENT_CHAR == '|')
		change_state(scanner, &state_3);
	else
		scanner->tk_type = PIPE;
}

void	state_1(t_scanner *scanner)
{
	if (CURRENT_CHAR == '|')
		change_state(scanner, &state_2);
	else if (CURRENT_CHAR == '>')
		change_state(scanner, &state_4);
	else if (CURRENT_CHAR == '<')
		change_state(scanner, &state_6);
	else if (CURRENT_CHAR == '&')
		change_state(scanner, &state_8);
	else if (CURRENT_CHAR == ';')
		change_state(scanner, &state_10);
	else if (CURRENT_CHAR == '\'')
		change_state(scanner, &state_12);
	else if (CURRENT_CHAR == '"')
		change_state(scanner, &state_13);
	else if (CURRENT_CHAR == '\\')
		change_state(scanner, &state_16);
	else
		state_15(scanner);
}
