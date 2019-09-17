/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/09/17 13:27:00 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	lexer_tokenlstiter(t_tokenlst *lst, void (*f)(t_tokenlst *elem))
{
	if (lst == NULL || f == NULL)
		return ;
	f(lst);
	lexer_tokenlstiter(lst->next, f);
}

int		shell_close_quote_and_esc(t_vshdata *data)
{
	int ret;

	ret = FUNCT_SUCCESS;
	while (ret == FUNCT_SUCCESS)
	{
		if (shell_close_unclosed_quotes(data) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		ret = shell_handle_escaped_newlines(data);
		if (ret == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}

void	shell_clear_input_data(char **line, t_ast **ast, t_tokenlst **token_lst)
{
	ft_strdel(line);
	parser_astdel(ast);
	lexer_tokenlstdel(token_lst);
}

void	shell_start(t_vshdata *data)
{
	t_tokenlst	*token_lst;
	t_ast		*ast;

	token_lst = NULL;
	ast = NULL;
	while (true)
	{
		shell_clear_input_data(&data->line->line, &ast, &token_lst);
		shell_display_prompt(data, REGULAR_PROMPT);
		if (input_read(data) == FUNCT_ERROR ||
			shell_close_quote_and_esc(data) == FUNCT_ERROR ||
			history_expansion(data) != FUNCT_SUCCESS)
			continue ;
		ft_putchar('\n');
		if (history_line_to_array(data->history->history, &data->line->line)
			== FUNCT_ERROR || lexer(&data->line->line, &token_lst) !=
			FUNCT_SUCCESS || shell_dless_input(data, &token_lst) !=
			FUNCT_SUCCESS || alias_expansion(data, &token_lst, NULL) !=
			FUNCT_SUCCESS || token_lst->next->type == NEWLINE ||
			parser_start(&token_lst, &ast) != FUNCT_SUCCESS)
			continue ;
		exec_complete_command(ast, data);
	}
}
