/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/07/28 18:34:10 by omulder       ########   odam.nl         */
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

int		shell_start(t_vshdata *vshdata)
{
	int			status;
	char		*line;
	t_tokenlst	*token_lst;
	t_ast		*ast;

	g_state->exit_code = EXIT_SUCCESS;
	status = 1;
	line = NULL;
	token_lst = NULL;
	ast = NULL;
	while (status != CTRLD)
	{
		shell_display_prompt();
		if (input_read(vshdata, &line, &status) == FUNCT_ERROR)
			continue;
		if (shell_quote_checker(vshdata, &line, &status) == FUNCT_ERROR)
			continue ;
		ft_putchar('\n');
		if (history_line_to_array(vshdata->history, &line) == FUNCT_ERROR)
			continue ;
		#ifdef DEBUG
		ft_printf("\n>>>> LINE <<<<\n%s\n\n>>>> TOKEN_LST <<<<\n", line);
		#endif
		if (lexer(&line, &token_lst) != FUNCT_SUCCESS)
			continue ;
		if (shell_dless_input(vshdata, &token_lst) != FUNCT_SUCCESS)
			continue ;
		if (alias_expansion(vshdata, &token_lst, NULL) != FUNCT_SUCCESS)
			continue ;
		if ((token_lst->next)->type == NEWLINE)
		{
			lexer_tokenlstdel(&token_lst);
			continue ;
		}

		#ifdef DEBUG
 		lexer_tokenlstiter(token_lst, print_node);
		#endif
		if (parser_start(&token_lst, &ast) != FUNCT_SUCCESS)
			continue ;
		#ifdef DEBUG
		ft_putstr("\n\n\nTREE:\n\n");
		print_tree(ast);
		#endif
		exec_start(ast, vshdata, 0);
		parser_astdel(&ast);
	}
	return (FUNCT_SUCCESS);
}
