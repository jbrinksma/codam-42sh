/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/06/05 17:08:47 by tde-jong      ########   odam.nl         */
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

int		shell_start(t_envlst *envlst)
{
	int			status;
	int			exit_code;
	char		*line;
	t_tokenlst	*token_lst;
	t_ast		*ast;

	exit_code = EXIT_SUCCESS;
	status = 1;
	line = NULL;
	token_lst = NULL;
	ast = NULL;
	while (status != CTRLD)
	{
		shell_display_prompt();
		status = input_read(&line);
		while (shell_quote_checker(&line) != FUNCT_SUCCESS)
			continue ;
		history_line_to_array(line);
		#ifdef DEBUG
		ft_printf("\n>>>> LINE <<<<\n%s\n\n>>>> TOKEN_LST <<<<\n", line);
		#endif
		if (lexer(&line, &token_lst) != FUNCT_SUCCESS)
			continue ;
		#ifdef DEBUG
		lexer_tokenlstiter(token_lst, print_node);
		#endif
		if (shell_dless_input(token_lst) != FUNCT_SUCCESS)
			continue ;
		#ifdef DEBUG
 		lexer_tokenlstiter(token_lst, print_node);
		#endif
		if (parser_start(&token_lst, &ast) != FUNCT_SUCCESS)
			continue ;
		#ifdef DEBUG
		print_tree(ast);
		#endif
		exec_start(ast, envlst, &exit_code);
		parser_astdel(&ast);
		/* ADD EVALUATOR */
		/* ADD EXPANSION FUNC ? */
		lexer_tokenlstdel(&token_lst);
		ft_putchar('\n');
		ft_strdel(&line);
	}
	return (FUNCT_SUCCESS);
}
