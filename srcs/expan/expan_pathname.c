/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expan_pathname.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 12:06:36 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/22 11:30:46 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Copies first node of expan over the current ast node but keeps
**	the ast->right intact to save the pointer to redirections and assigns
*/

static void	copy_first_expan_to_ast(t_ast *ast, t_ast **expanded)
{
	t_ast *to_free;

	ast->flags = 0;
	ft_strdel(&ast->value);
	ast->value = (*expanded)->value;
	ast->left = (*expanded)->left;
	to_free = *expanded;
	*expanded = (*expanded)->left;
	ft_memdel((void**)&to_free);
}

/*
**	If a pathname expansion has taken place
**	insert_expan_into_ast first copies the first node of the new expanded ast
**	into the current ast node. After that it inserts the
**	rest of the expanded ast behind the original ast node.
**	insert_expan_into_ast will aslo set the current ast node to the next so that
**	expan_pathname will continue globbing the next node of the ast.
*/

static void	insert_expan_into_ast(t_ast **ast, t_ast *expanded)
{
	t_ast *to_expand;

	to_expand = (*ast)->left;
	if (expanded == NULL)
	{
		(*ast) = (*ast)->left;
		return ;
	}
	copy_first_expan_to_ast(*ast, &expanded);
	if (expanded == NULL)
	{
		(*ast)->left = to_expand;
		*ast = to_expand;
		return ;
	}
	while (expanded->left != NULL)
		expanded = expanded->left;
	expanded->left = to_expand;
	*ast = to_expand;
}

/*
**	expan_pathname will go through all words of a command and try to glob them.
**	insert_expan_into_ast will then insert the expanded ast list into the
**	current ast node
*/

int			expan_pathname(t_ast *ast)
{
	t_glob	glob_data;

	while (ast != NULL)
	{
		glob_data.expanded = NULL;
		glob_data.cwd_len = 0;
		if (glob_expand_word(&glob_data, ast->value) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		insert_expan_into_ast(&ast, glob_data.expanded);
	}
	return (FUNCT_SUCCESS);
}
