/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_6_10.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:12:00 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/24 11:38:54 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	state_semicol(t_scanner *scanner)
{
	scanner->tk_type = SEMICOL;
}

void	state_andif(t_scanner *scanner)
{
	scanner->tk_type = AND_IF;
}

void	state_bg(t_scanner *scanner)
{
	if (CURRENT_CHAR == '&')
		change_state(scanner, &state_andif);
	else
		scanner->tk_type = BG;
}

void	state_dless(t_scanner *scanner)
{
	scanner->tk_type = DLESS;
}

void	state_sless(t_scanner *scanner)
{
	if (CURRENT_CHAR == '<')
		change_state(scanner, &state_dless);
	else if (CURRENT_CHAR == '&')
		change_state(scanner, &state_lessand);
	else
		scanner->tk_type = SLESS;
}
