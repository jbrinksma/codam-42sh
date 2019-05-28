/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_if_else.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:12:00 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/27 16:50:01 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	lexer_state_pipe(t_scanner *scanner)
{
	if (CURRENT_CHAR == '|')
		lexer_change_state(scanner, &lexer_state_orif);
	else
		scanner->tk_type = PIPE;
}

void	lexer_state_bg(t_scanner *scanner)
{
	if (CURRENT_CHAR == '&')
		lexer_change_state(scanner, &lexer_state_andif);
	else
		scanner->tk_type = BG;
}

void	lexer_state_sless(t_scanner *scanner)
{
	if (CURRENT_CHAR == '<')
		lexer_change_state(scanner, &lexer_state_dless);
	else if (CURRENT_CHAR == '&')
		lexer_change_state(scanner, &lexer_state_lessand);
	else
		scanner->tk_type = SLESS;
}

void	lexer_state_sgreat(t_scanner *scanner)
{
	if (CURRENT_CHAR == '>')
		lexer_change_state(scanner, &lexer_state_dgreat);
	else if (CURRENT_CHAR == '&')
		lexer_change_state(scanner, &lexer_state_greatand);
	else
		scanner->tk_type = SGREAT;
}
