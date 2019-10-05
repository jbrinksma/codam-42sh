/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/14 15:14:31 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/01 12:29:58 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	The lexer creates a token list which will be send to the parser.
**	In the lexer, the scanner will create the list of tokens.
*/

t_tokenlst	*lexer_tokenlstnew(t_tokens type, char *value, int flags)
{
	t_tokenlst	*new;

	new = (t_tokenlst*)ft_memalloc(sizeof(t_tokenlst));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->value = value;
	new->flags = flags;
	return (new);
}

/*
**	Adds token to the end of the token_lst if it already has list items, and
**	creates the first list item if it has no items yet.
*/

int			lexer_tokenlstaddback(t_tokenlst **token_lst, t_tokens type,
			char *value, int flags)
{
	if (*token_lst == NULL)
	{
		*token_lst = lexer_tokenlstnew(type, value, flags);
		if (*token_lst == NULL)
			return (FUNCT_ERROR);
		return (FUNCT_SUCCESS);
	}
	else if ((*token_lst)->next == NULL)
	{
		(*token_lst)->next = lexer_tokenlstnew(type, value, flags);
		if ((*token_lst)->next == NULL)
			return (FUNCT_ERROR);
		return (FUNCT_SUCCESS);
	}
	else
		return (lexer_tokenlstaddback(&(*token_lst)->next, type, value, flags));
}

/*
**	The token_lst that is made through lexer_scanner is started off with
**	a START token, and finished off with an END token.
*/

int			lexer(char **line, t_tokenlst **token_lst)
{
	if (lexer_tokenlstaddback(token_lst, START, NULL, NO_FLAGS)
		!= FUNCT_SUCCESS)
		return (lexer_error(line));
	if (lexer_scanner(*line, *token_lst) != FUNCT_SUCCESS)
		return (lexer_error(line));
	if (lexer_tokenlstaddback(token_lst, END, NULL, NO_FLAGS) != FUNCT_SUCCESS)
		return (lexer_error(line));
	ft_strdel(line);
	return (FUNCT_SUCCESS);
}
