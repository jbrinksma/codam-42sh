/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 19:54:55 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/27 17:27:36 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

t_ast	*parser_new_node(t_tokenlst *token)
{
	t_ast *node;

	node = (t_ast*)ft_memalloc(sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = token->type;
	node->flags = token->flags;
	if (token->value != NULL)
	{
		node->value = ft_strdup(token->value);
		if (node->value == NULL)
			return (NULL);
	}
	else
		node->value = NULL;
	node->child = NULL;
	node->sibling = NULL;
	return (node);
}

bool	parser_add_sibling(t_tokenlst **token_lst, t_ast **ast,
		bool (*parse_priority_x)(t_tokenlst **, t_ast **))
{
	t_ast *sibling;

	sibling = NULL;
	if (parse_priority_x(token_lst, &sibling) != true)
		return (false);
	(*ast)->sibling = sibling;
	return (true);
}

bool	parser_add_astnode(t_tokenlst **token_lst, t_ast **ast)
{
	t_ast *new_node;

	new_node = parser_new_node(*token_lst);
	if (new_node == NULL)
	{
		(*token_lst)->flags |= T_MALLOC_ERROR;
		return (false);
	}
	new_node->child = *ast;
	new_node->sibling = NULL;
	*ast = new_node;
	*token_lst = (*token_lst)->next;
	return (true);
}
