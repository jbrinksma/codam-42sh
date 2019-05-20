/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_6_10.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:12:00 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/19 13:48:07 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	state_10(t_scanner *scanner)
{
	scanner->tk_type = SEMICOL;
}

void	state_9(t_scanner *scanner)
{
	scanner->tk_type = AND_IF;
}

void	state_8(t_scanner *scanner)
{
	if (CURRENT_CHAR == '&')
		change_state(scanner, &state_9);
	else
		scanner->tk_type = BG;
}

void	state_7(t_scanner *scanner)
{
	scanner->tk_type = DLESS;
}

void	state_6(t_scanner *scanner)
{
	if (CURRENT_CHAR == '<')
		change_state(scanner, &state_7);
	else if (CURRENT_CHAR == '&')
		change_state(scanner, &state_17);
	else
		scanner->tk_type = SLESS;
}
