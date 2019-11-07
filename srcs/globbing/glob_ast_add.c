/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_ast_add.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 14:38:28 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/07 14:13:43 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static t_ast	*ast_new_node(char *value, t_tokens type, char flags)
{
	t_ast *node;

	node = (t_ast*)ft_memalloc(sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->flags = flags;
	if (value != NULL)
	{
		node->value = ft_strdup(value);
		if (node->value == NULL)
			return (NULL);
	}
	else
		node->value = NULL;
	return (node);
}

static void		glob_insert_ast(t_ast **ast, t_ast *new)
{
	t_ast	*probe;

	probe = *ast;
	if (ft_strcmp(probe->value, new->value) > 0)
	{
		new->left = probe;
		*ast = new;
		return ;
	}
	while (probe->left != NULL)
	{
		if (ft_strcmp(probe->left->value, new->value) > 0)
		{
			new->left = probe->left;
			probe->left = new;
			return ;
		}
		probe = probe->left;
	}
	probe->left = new;
}

/*
**	glob_ast_add_left always adds new nodes to the left side of our ast
**	When ast already exists it will insert the new node in a way that the list
**	remains in alphabetical order
*/

int				glob_ast_add_left(t_ast **ast, char *value,
				t_tokens type, char flags)
{
	t_ast	*new_node;

	new_node = ast_new_node(value, type, flags);
	if (new_node == NULL)
		return (FUNCT_ERROR);
	new_node->is_expanded = true;
	if (*ast == NULL)
		*ast = new_node;
	else
		glob_insert_ast(ast, new_node);
	return (FUNCT_SUCCESS);
}
