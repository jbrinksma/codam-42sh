/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 19:13:12 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/05 13:21:34 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool		parser_cmd_suffix(t_tokenlst **token_lst, t_ast **cmd,
	t_ast **last_cmd_arg, t_ast **last_prefix)
{
	t_ast *new_ast;

	new_ast = NULL;
	if (TK_TYPE == IO_NUMBER || tool_is_redirect_tk(TK_TYPE) == true)
	{
		if (parser_io_redirect(token_lst, &new_ast) == false)
			return (false);
		if ((*cmd)->right == NULL)
			(*cmd)->right = new_ast;
		else
			(*last_prefix)->left = new_ast;
		*last_prefix = new_ast;
		if (parser_cmd_suffix(token_lst, cmd, last_cmd_arg, last_prefix)
			== false)
			return (false);
	}
	else if (TK_TYPE == WORD || TK_TYPE == ASSIGN)
	{
		if (parser_cmd_param(token_lst, cmd, last_cmd_arg, last_prefix)
			== false)
			return (false);
	}
	return (true);
}

bool		parser_cmd_param(t_tokenlst **token_lst, t_ast **cmd,
	t_ast **last_cmd_arg, t_ast **last_prefix)
{
	t_ast *new_ast;

	new_ast = NULL;
	if (parser_add_astnode(token_lst, &new_ast) == false)
		return (false);
	if (*last_cmd_arg == NULL)
		(*cmd)->left = new_ast;
	else
		(*last_cmd_arg)->left = new_ast;
	*last_cmd_arg = new_ast;
	if (parser_cmd_suffix(token_lst, cmd, last_cmd_arg, last_prefix)
		== false)
		return (false);
	return (true);
}

static bool	parser_cmd_prefix(t_tokenlst **token_lst, t_ast **prefix,
	t_ast **last_prefix)
{
	t_ast *new_prefix;

	new_prefix = NULL;
	if (TK_TYPE == ASSIGN || TK_TYPE == IO_NUMBER ||
		tool_is_redirect_tk(TK_TYPE) == true)
	{
		if (TK_TYPE == ASSIGN)
		{
			if (parser_add_astnode(token_lst, &new_prefix) == false)
				return (parser_return_del(prefix));
		}
		else if (parser_io_redirect(token_lst, &new_prefix) == false)
			return (parser_return_del(prefix));
		if (*prefix == NULL)
			*prefix = new_prefix;
		else
			(*last_prefix)->left = new_prefix;
		*last_prefix = new_prefix;
		if (parser_cmd_prefix(token_lst, prefix, last_prefix) == false)
			return (false);
	}
	return (true);
}

static bool	parser_cmd_word(t_tokenlst **token_lst, t_ast **cmd,
			t_ast **prefix)
{
	if (TK_TYPE == WORD)
	{
		if (parser_add_astnode(token_lst, cmd) == false)
			return (false);
		(*cmd)->right = *prefix;
		return (true);
	}
	else if (*prefix != NULL)
	{
		*cmd = *prefix;
		return (true);
	}
	else
		return (false);
}

bool		parser_command(t_tokenlst **token_lst, t_ast **cmd)
{
	t_ast	*prefix;
	t_ast	*last_prefix;
	t_ast	*last_cmd_arg;

	prefix = NULL;
	last_prefix = NULL;
	last_cmd_arg = NULL;
	if (TK_TYPE == WORD || TK_TYPE == ASSIGN || TK_TYPE == IO_NUMBER ||
		tool_is_redirect_tk(TK_TYPE) == true)
	{
		if (parser_cmd_prefix(token_lst, &prefix, &last_prefix) == false)
			return (false);
		if (parser_cmd_word(token_lst, cmd, &prefix) == false)
			return (parser_return_del(cmd));
		if (parser_cmd_suffix(token_lst, cmd, &last_cmd_arg, &last_prefix)
			== false)
			return (parser_return_del(cmd));
		return (true);
	}
	else
		return (false);
}
