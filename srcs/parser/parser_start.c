/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_start.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 19:58:40 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/29 14:35:59 by omulder       ########   odam.nl         */
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
				return (false);
			if (parser_add_sibling(token_lst, ast, &parser_command) != true)
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
		while (TK_TYPE == AND_IF ||
			TK_TYPE == OR_IF)
		{
			if (parser_add_astnode(token_lst, ast) == false)
				return (false);
			if (parser_add_sibling(token_lst, ast, &parser_pipe_sequence)
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
				return (false);
			if (TK_TYPE != END)
			{
				if (parser_add_sibling(token_lst, ast, &parser_list) == false)
					return (false);
			}
		}
		return (true);
	}
	return (false);
}

static bool	parser_complete_command(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_list(token_lst, ast) == true && TK_TYPE == END)
		return (true);
	return (false);
}

int			parser_start(t_tokenlst **token_lst, t_ast **ast)
{
	t_tokenlst	*tmp;

	tmp = (*token_lst)->next;
	if (parser_complete_command(&tmp, ast) != true)
	{
		if ((tmp)->flags & T_MALLOC_ERROR)
			ft_putstr("vsh: parser: malloc error\n");
		else
			ft_printf("vsh: syntax error near unexpected token `%s'\n",
			parser_return_token_str((tmp)->type));
		lexer_tokenlstdel(token_lst);
		parser_astdel(ast);
		return (FUNCT_FAILURE);
	}
	lexer_tokenlstdel(token_lst);
	return (FUNCT_SUCCESS);
}
