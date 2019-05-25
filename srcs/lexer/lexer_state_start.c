/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_start.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:10:51 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/25 14:41:40 by mavan-he      ########   odam.nl         */
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

void	state_orif(t_scanner *scanner)
{
	scanner->tk_type = OR_IF;
}

void	state_start(t_scanner *scanner)
{
	if (CURRENT_CHAR == '$')
		scanner->flags |= T_FLAG_HASDOLLAR;
	if (CURRENT_CHAR == '"')
		scanner->flags ^= T_STATE_DQUOTE;
	if (CURRENT_CHAR == '\'')
		scanner->flags ^= T_STATE_SQUOTE;
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
	else if (CURRENT_CHAR == '\\')
		change_state(scanner, &state_word_esc);
	else if (ft_isdigit(CURRENT_CHAR))
		change_state(scanner, &state_ionum);
	else
		change_state(scanner, &state_word);
}
