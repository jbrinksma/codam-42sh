/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/11/04 10:45:09 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

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

static void	shell_start_new_prompt(t_vshdata **data, t_ast **ast,
				t_tokenlst **token_lst)
{
	shell_clear_input_data(&(*data)->line->line, ast, token_lst);
	shell_display_prompt(*data, REGULAR_PROMPT);
}

static void	shell_start_failed(void)
{
	g_state->exit_code = EXIT_FATAL;
	ft_eprintf(E_FAIL_DUP_FD);
}

void		shell_start(t_vshdata *data)
{
	t_tokenlst	*token_lst;
	t_ast		*ast;

	token_lst = NULL;
	ast = NULL;
	if (backup_stdfds() == FUNCT_ERROR)
		return (shell_start_failed());
	while (true)
	{
		jobs_notify_pool();
		shell_start_new_prompt(&data, &ast, &token_lst);
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
