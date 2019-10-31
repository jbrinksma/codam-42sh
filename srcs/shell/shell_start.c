/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/10/29 14:12:14 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		lexer_tokenlstiter(t_tokenlst *lst, void (*f)(t_tokenlst *elem))
{
	if (lst == NULL || f == NULL)
		return ;
	f(lst);
	lexer_tokenlstiter(lst->next, f);
}

int			shell_close_quote_and_esc(t_vshdata *data)
{
	int		ret;
	bool	ctrl_d;

	ret = FUNCT_SUCCESS;
	ctrl_d = false;
	while (ret == FUNCT_SUCCESS)
	{
		ret = shell_close_unclosed_quotes(data);
		if (ret == FUNCT_ERROR || ret == NEW_PROMPT)
			return (ret);
		else if (ret == IR_EOF)
			ctrl_d = true;
		ret = shell_handle_escaped_newlines(data);
		if (ret == FUNCT_ERROR || ret == NEW_PROMPT)
			return (ret);
		else if (ret == IR_EOF)
			ctrl_d = true;
	}
	if (ctrl_d == true)
		return (IR_EOF);
	return (FUNCT_SUCCESS);
}

void		shell_clear_input_data(char **line, t_ast **ast,
				t_tokenlst **token_lst)
{
	ft_strdel(line);
	parser_astdel(ast);
	lexer_tokenlstdel(token_lst);
}

static int	pre_lexer_reading(t_vshdata *data)
{
	int			ret;
	bool		ctrl_d;

	ctrl_d = false;
	ret = input_read(data);
	if (ret == FUNCT_ERROR)
	{
		ft_eprintf(E_READ_STR);
		exit(EXIT_FAILURE);
	}
	if (ret == IR_EOF)
		ctrl_d = true;
	if (ret != FUNCT_ERROR && ret != NEW_PROMPT)
	{
		ret = shell_close_quote_and_esc(data);
		if (ret == IR_EOF)
			ctrl_d = true;
		if (ret != FUNCT_ERROR && ret != NEW_PROMPT)
			ret = FUNCT_SUCCESS;
	}
	if (ret == FUNCT_SUCCESS && ctrl_d == false)
		ft_putchar('\n');
	return (ret);
}

void		shell_start(t_vshdata *data)
{
	t_tokenlst	*token_lst;
	t_ast		*ast;

	token_lst = NULL;
	ast = NULL;
	while (true)
	{
		jobs_handle_finished_jobs();
		shell_clear_input_data(&data->line->line, &ast, &token_lst);
		shell_display_prompt(data, REGULAR_PROMPT);
		if (pre_lexer_reading(data) != FUNCT_SUCCESS)
			continue ;
		if (history_expansion(data) != FUNCT_SUCCESS ||
			history_add_item(data->history, data->line->line)
			== FUNCT_ERROR || lexer(&data->line->line, &token_lst) !=
			FUNCT_SUCCESS || shell_dless_input(data, &token_lst) !=
			FUNCT_SUCCESS || alias_expansion(data, &token_lst, NULL) !=
			FUNCT_SUCCESS)
			continue ;
		if (token_lst->next->type == NEWLINE || token_lst->next->type == END
			|| parser_start(&token_lst, &ast) != FUNCT_SUCCESS)
			continue ;
		exec_complete_command(ast, data);
	}
}
