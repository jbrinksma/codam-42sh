/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/08/19 18:31:38 by omulder       ########   odam.nl         */
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

int		shell_close_quote_and_esc(t_vshdata *vshdata, char **line,
				int *status)
{
	int ret;

	ret = FUNCT_SUCCESS;
	while (ret == FUNCT_SUCCESS)
	{
		if (shell_close_unclosed_quotes(vshdata, line, status) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		ret = shell_handle_escaped_newlines(vshdata, line, status);
		if (ret == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}

int		shell_start(t_vshdata *vshdata)
{
	int			status;
	char		*line;
	t_tokenlst	*token_lst;
	t_ast		*ast;

	status = 1;
	line = NULL;
	token_lst = NULL;
	ast = NULL;
	env_add_extern_value(vshdata, "OLDPWD", "");
	while (status != CTRLD)
	{
		ft_strdel(&line);
		parser_astdel(&ast);
		lexer_tokenlstdel(&token_lst);
	shell_display_prompt(vshdata->envlst);
	if (input_read(vshdata, &line, &status) == FUNCT_ERROR)
		continue;
	if (shell_close_quote_and_esc(vshdata, &line, &status) == FUNCT_ERROR)
		continue ;
	ft_putchar('\n');
	if (history_line_to_array(vshdata->history, &line) == FUNCT_ERROR)
		continue ;
	if (lexer(&line, &token_lst) != FUNCT_SUCCESS)
		continue ;
	if (shell_dless_input(vshdata, &token_lst) != FUNCT_SUCCESS)
		continue ;
	if (alias_expansion(vshdata, &token_lst, NULL) != FUNCT_SUCCESS)
		continue ;
	if ((token_lst->next)->type == NEWLINE)
		continue ;
	if (parser_start(&token_lst, &ast) != FUNCT_SUCCESS)
		continue ;
	exec_complete_command(ast, vshdata);
	}
	return (FUNCT_SUCCESS);
}
