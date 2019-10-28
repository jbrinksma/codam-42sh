/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_lexer_states.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 21:10:48 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/21 16:11:51 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void		glob_lexer_state_braced(t_globscanner *scanner)
{
	if (GLOB_CUR_CHAR == ']' && scanner->flags & GLOB_F_NEG)
		glob_lexer_finish(scanner, GLOB_BRACENEG);
	else if (GLOB_CUR_CHAR == ']')
		glob_lexer_finish(scanner, GLOB_BRACEPOS);
	else if (GLOB_CUR_CHAR == '\\' && scanner->word[scanner->word_index + 1] ==
	'!' && scanner->tk_len == 1)
	{
		scanner->flags |= GLOB_F_NEG;
		glob_lexer_changestate(scanner, &glob_lexer_state_braced);
	}
	else if (GLOB_CUR_CHAR != '\0')
		glob_lexer_changestate(scanner, &glob_lexer_state_braced);
	else
		return ;
}

static void		glob_lexer_state_str(t_globscanner *scanner)
{
	scanner->tk_type = GLOB_STR;
	if (GLOB_CUR_CHAR == '\0'
	|| GLOB_CUR_CHAR == '?'
	|| GLOB_CUR_CHAR == '['
	|| GLOB_CUR_CHAR == '*'
	|| GLOB_CUR_CHAR == '/')
		return ;
	else
		glob_lexer_changestate(scanner, &glob_lexer_state_str);
}

void			glob_lexer_state_start(t_globscanner *scanner)
{
	if (GLOB_CUR_CHAR == '*')
		glob_lexer_finish(scanner, GLOB_WILD);
	else if (GLOB_CUR_CHAR == '?')
		glob_lexer_finish(scanner, GLOB_QUEST);
	else if (GLOB_CUR_CHAR == '/')
		glob_lexer_finish(scanner, GLOB_SLASH);
	else if (ft_strnequ(&GLOB_CUR_CHAR, "./", 2) == true)
	{
		scanner->tk_len++;
		scanner->word_index++;
		glob_lexer_finish(scanner, GLOB_DOTSLASH);
	}
	else if (ft_strnequ(&GLOB_CUR_CHAR, "../", 3) == true)
	{
		scanner->tk_len += 2;
		scanner->word_index += 2;
		glob_lexer_finish(scanner, GLOB_DOTDOTSLASH);
	}
	else if (GLOB_CUR_CHAR == '[')
		glob_lexer_changestate(scanner, &glob_lexer_state_braced);
	else if (GLOB_CUR_CHAR != '\0')
		glob_lexer_changestate(scanner, &glob_lexer_state_str);
}
