/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_lexer_helpers.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 20:37:43 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/21 11:30:43 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void			glob_lexer_addchar(t_globscanner *scanner)
{
	scanner->tk_len++;
	scanner->word_index++;
}

void			glob_lexer_finish(t_globscanner *scanner, t_globtokens type)
{
	glob_lexer_addchar(scanner);
	scanner->tk_type = type;
}

void			glob_lexer_changestate(t_globscanner *scanner,
					void (*state)(t_globscanner *scanner))
{
	glob_lexer_addchar(scanner);
	state(scanner);
}
