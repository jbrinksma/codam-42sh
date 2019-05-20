/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/14 15:14:31 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/19 16:01:29 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	The lexer creates a token list which will be send to the parser.
**	In the lexer, the scanner will create the list of tokens.
**	After that, the evaluator will remove any unnecessary '\', '\'' and '"'.
*/

int			lexer(char *line, t_list **token_lst)
{
	t_token token;
	t_list	*new;

	token.type = START;
	new = ft_lstnew(&token, sizeof(t_token));
	if (new == NULL)
		return (lexer_error(token_lst));
	ft_lstadd(token_lst, new);
	if (lexer_scanner(line, *token_lst) == FUNCT_ERROR)
		return (lexer_error(token_lst));
	token.type = END;
	if (add_tk_to_lst(token_lst, &token) == FUNCT_ERROR)
		return (lexer_error(token_lst));
	evaluator(*token_lst);
	return (FUNCT_SUCCESS);
}
