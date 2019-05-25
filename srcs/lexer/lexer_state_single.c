/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_state_single.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 12:14:21 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/25 14:41:50 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	state_dgreat(t_scanner *scanner)
{
	scanner->tk_type = DGREAT;
}

void	state_dless(t_scanner *scanner)
{
	scanner->tk_type = DLESS;
}

void	state_greatand(t_scanner *scanner)
{
	scanner->tk_type = GREATAND;
}

void	state_lessand(t_scanner *scanner)
{
	scanner->tk_type = LESSAND;
}
