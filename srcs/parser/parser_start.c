/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 19:58:40 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/16 12:40:30 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Function names in this file refer to the vsh grammer.
*/

static bool	parser_pipe_sequence(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_command(token_lst, ast) == true)
	{
		while (TK_TYPE == PIPE)
		{
			if (parser_add_astnode(token_lst, ast) == false)
				return (parser_return_del(ast));
			if (parser_add_right(token_lst, ast, &parser_command) != true)
				return (false);
		}
		return (true);
	}
	return (false);
}

static bool	parser_and_or(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_pipe_sequence(token_lst, ast) == true)
	{
		while (TK_TYPE == AND_IF || TK_TYPE == OR_IF)
		{
			if (parser_add_astnode(token_lst, ast) == false)
				return (parser_return_del(ast));
			if (parser_add_right(token_lst, ast, &parser_pipe_sequence)
				!= true)
				return (false);
		}
		return (true);
	}
	return (false);
}

static bool	parser_list(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_and_or(token_lst, ast) == true)
	{
		if (TK_TYPE == SEMICOL ||
			TK_TYPE == BG)
		{
			if (parser_add_astnode(token_lst, ast) == false)
				return (parser_return_del(ast));
			if (TK_TYPE != NEWLINE)
			{
				if (parser_add_right(token_lst, ast, &parser_list) == false)
					return (false);
			}
		}
		return (true);
	}
	return (false);
}

static bool	parser_complete_command(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_list(token_lst, ast) == true && TK_TYPE == NEWLINE)
		return (true);
	return (parser_return_del(ast));
}

int			parser_start(t_tokenlst **token_lst, t_ast **ast)
{
	t_tokenlst	*tmp;
	int			ret;

	tmp = (*token_lst)->next;
	if (parser_complete_command(&tmp, ast) != true)
	{
		ret = FUNCT_FAILURE;
		if ((tmp)->flags & T_MALLOC_ERROR)
		{
			ret = FUNCT_ERROR;
			ft_eprintf(E_N_ALLOC_STR, "parser");
		}
		else
			ft_eprintf(E_SYNTAX_P,
			parser_return_token_str((tmp)->type));
		return (ret);
	}
	return (FUNCT_SUCCESS);
}
