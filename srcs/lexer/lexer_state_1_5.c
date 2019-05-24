/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_1_5.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:10:51 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/24 11:35:48 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	state_dgreat(t_scanner *scanner)
{
	scanner->tk_type = DGREAT;
}

void	state_sgreat(t_scanner *scanner)
{
	if (CURRENT_CHAR == '>')
		change_state(scanner, &state_dgreat);
	else if (CURRENT_CHAR == '&')
		change_state(scanner, &state_greatand);
	else
		scanner->tk_type = SGREAT;
}

void	state_orif(t_scanner *scanner)
{
	scanner->tk_type = OR_IF;
}

void	state_pipe(t_scanner *scanner)
{
	if (CURRENT_CHAR == '|')
		change_state(scanner, &state_orif);
	else
		scanner->tk_type = PIPE;
}

void	state_start(t_scanner *scanner)
{
	if (CURRENT_CHAR == '|')
		change_state(scanner, &state_pipe);
	else if (CURRENT_CHAR == '>')
		change_state(scanner, &state_sgreat);
	else if (CURRENT_CHAR == '<')
		change_state(scanner, &state_sless);
	else if (CURRENT_CHAR == '&')
		change_state(scanner, &state_bg);
	else if (CURRENT_CHAR == ';')
		change_state(scanner, &state_semicol);
	else if (CURRENT_CHAR == '\'')
		change_state(scanner, &state_squote);
	else if (CURRENT_CHAR == '"')
		change_state(scanner, &state_dquote);
	else if (CURRENT_CHAR == '\\')
		change_state(scanner, &state_word_esc);
	else
		state_word(scanner);
}
