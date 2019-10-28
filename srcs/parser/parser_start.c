/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 19:58:40 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/22 14:00:02 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Function names in this file refer to the vsh grammer.
*/

/*
**	After parser_command, we can have a PIPE token 
**	In that case the PIPE token is added to the ast
**	We then add a parser command to the left of this node
**	in case of another PIPE we add the previous ast to the left
**	and another parser_commmand to the right
**	If the current token is not a AND_IF or OR_IF token we return
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

/*
**	After parser_pipe_sequence, we can have an AND_IF or OR_IF token 
**	In that case the current token is added to the ast
**	We then expect another pipe sequence or another and_or
**	which is added to the right of the AND_IF or OR_IF node
**	If the current token is not a AND_IF or OR_IF token we return
*/

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

/*
**	After parser_and_or is done, we expect an END, NEWLINE, SEMICOL or BG token 
**	In a case of a SEMICOL or BG token the token is added to the ast
**	We then continue with another parser_list if there is no END or NEWLINE
**	If the current token is an END or NEWLINE token we return
*/

static bool	parser_list(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_and_or(token_lst, ast) == true)
	{
		if (TK_TYPE == SEMICOL ||
			TK_TYPE == BG)
		{
			if (parser_add_astnode(token_lst, ast) == false)
				return (parser_return_del(ast));
			if (TK_TYPE != NEWLINE && TK_TYPE != END)
			{
				if (parser_add_right(token_lst, ast, &parser_list) == false)
					return (false);
			}
		}
		return (true);
	}
	return (false);
}

/*
**	After parser list is done, we expect an END or NEWLINE token
**	If the current token is neither of these we return syntax error
*/

static bool	parser_complete_command(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_list(token_lst, ast) == true && (TK_TYPE == NEWLINE
		|| TK_TYPE == END))
		return (true);
	return (parser_return_del(ast));
}

/*
**	The parser creates the abstract syntax tree (ast)
**	We skip the first node (start node) in token_lst
**	We then start with parser_complete_command
**	If the token order is wrong we return syntax error
*/

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
		{
			ft_eprintf(E_SYNTAX_P,
			parser_return_token_str((tmp)->type));
			g_state->exit_code = EXIT_FAILURE;
		}
		return (ret);
	}
	return (FUNCT_SUCCESS);
}
