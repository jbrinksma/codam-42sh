/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/05/16 17:56:38 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		shell_start(void)
{
	int			status;
	char		*line;
	t_list		*token_lst;

	status = 1;
	line = NULL;
	token_lst = NULL;
	while (status != CTRLD)
	{
		shell_display_prompt();
		status = input_read(&line);
		if (lexer(line, &token_lst) != FUNCT_SUCCESS)
		{
			ft_strdel(&line);
			continue ;
		}
		#ifdef DEBUG
		ft_printf("\n>>>> LINE <<<<\n%s\n\n>>>> TOKEN_LST <<<<\n", line);
		ft_lstiter(token_lst, print_node);
		#endif
		/* ADD EXPANSION FUNC ? */
		/* ADD PARSER */
		/* ADD EVALUATOR */
		/* ADD AST DEL */
		ft_lstdel(&token_lst, del_tk_node);
		ft_strdel(&line);
		ft_putendl("");
	}
	return (FUNCT_SUCCESS);
}
