/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 19:13:12 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/29 14:13:09 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static bool	parser_io_redirect(t_tokenlst **token_lst, t_ast **ast)
{
	t_ast *redir;

	redir = NULL;
	if (TK_TYPE == IO_NUMBER && parser_add_astnode(token_lst, ast) == false)
		return (false);
	if (tool_is_redirect_tk(TK_TYPE) == false ||
		parser_add_astnode(token_lst, ast) == false)
		return (false);
	if ((TK_TYPE != WORD && TK_TYPE != ASSIGN) ||
		parser_add_astnode(token_lst, &redir) == false)
		return (false);
	if ((*ast)->child == NULL)
		(*ast)->child = redir;
	else
		(*ast)->child->child = redir;
	(*ast)->sibling = (*ast)->child;
	(*ast)->child = NULL;
	return (true);
}

static bool	parser_cmd_suffix(t_tokenlst **token_lst, t_ast **suffix,
			t_ast **prefix)
{
	t_ast *next_ast;

	next_ast = NULL;
	if (TK_TYPE == IO_NUMBER || tool_is_redirect_tk(TK_TYPE) == true)
	{
		if (parser_io_redirect(token_lst, &next_ast) == false)
			return (false);
		if (*prefix == NULL)
			*prefix = next_ast;
		else
			(*prefix)->child = next_ast;
		if (parser_cmd_suffix(token_lst, suffix, &next_ast) == false)
			return (false);
	}
	else if (TK_TYPE == WORD || TK_TYPE == ASSIGN)
	{
		if (parser_add_astnode(token_lst, &next_ast) == false)
			return (false);
		if (*suffix == NULL)
			*suffix = next_ast;
		else
			(*suffix)->child = next_ast;
		if (parser_cmd_suffix(token_lst, &next_ast, prefix) == false)
			return (false);
	}
	return (true);
}

static bool	parser_cmd_prefix(t_tokenlst **token_lst,
			t_ast **ast, t_ast **prefix)
{
	t_ast *next_prefix;

	next_prefix = NULL;
	if (TK_TYPE == ASSIGN || TK_TYPE == IO_NUMBER ||
		tool_is_redirect_tk(TK_TYPE) == true)
	{
		if (TK_TYPE == ASSIGN)
		{
			if (parser_add_astnode(token_lst, ast) == false)
				return (false);
		}
		else if (parser_io_redirect(token_lst, ast) == false)
			return (false);
		*prefix = *ast;
		if (parser_cmd_prefix(token_lst, &next_prefix, prefix) == false)
			return (false);
		(*ast)->child = next_prefix;
	}
	return (true);
}

static bool	parser_cmd_word(t_tokenlst **token_lst, t_ast **ast,
			t_ast **prefix)
{
	if (TK_TYPE == WORD)
	{
		if (parser_add_astnode(token_lst, ast) == false)
			return (false);
		(*ast)->sibling = (*ast)->child;
		(*ast)->child = NULL;
		return (true);
	}
	else if (*ast != NULL)
	{
		*prefix = NULL;
		return (true);
	}
	else
		return (false);
}

bool		parser_command(t_tokenlst **token_lst, t_ast **ast)
{
	t_ast	*prefix;
	t_ast	*suffix;

	prefix = NULL;
	suffix = NULL;
	if (TK_TYPE == WORD || TK_TYPE == ASSIGN || TK_TYPE == IO_NUMBER ||
		tool_is_redirect_tk(TK_TYPE) == true)
	{
		if (parser_cmd_prefix(token_lst, ast, &prefix) == false)
			return (false);
		if (parser_cmd_word(token_lst, ast, &prefix) == false)
			return (false);
		if (parser_cmd_suffix(token_lst, &suffix, &prefix) == false)
			return (false);
		if ((*ast)->child == NULL)
			(*ast)->sibling = prefix;
		else
			(*ast)->sibling = (*ast)->child;
		(*ast)->child = suffix;
		return (true);
	}
	else
		return (false);
}
