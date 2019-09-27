/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/14 15:14:31 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/27 13:49:45 by tde-jong      ########   odam.nl         */
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

int			lexer(char **line, t_tokenlst **token_lst)
{
	if (lexer_tokenlstaddback(token_lst, START, NULL, 0) != FUNCT_SUCCESS)
		return (lexer_error(line));
	if (lexer_scanner(*line, *token_lst) != FUNCT_SUCCESS)
		return (lexer_error(line));
	if (lexer_tokenlstaddback(token_lst, END, NULL, 0) != FUNCT_SUCCESS)
		return (lexer_error(line));
	ft_strdel(line);
	return (FUNCT_SUCCESS);
}
