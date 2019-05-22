/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/05/21 19:37:59 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	tokenlstiter(t_tokenlst *lst, void (*f)(t_tokenlst *elem))
{
	if (lst == NULL || f == NULL)
		return ;
	f(lst);
	tokenlstiter(lst->next, f);
}

int		shell_start(void)
{
	int			status;
	char		*line;
	t_tokenlst	*lst;

	status = 1;
	line = NULL;
	lst = NULL;
	while (status != CTRLD)
	{
		shell_display_prompt();
		status = input_read(&line);
		if (lexer(line, &lst) != FUNCT_SUCCESS)
		{
			ft_strdel(&line);
			continue ;
		}
		#ifdef DEBUG
		ft_printf("\n>>>> LINE <<<<\n%s\n\n>>>> TOKEN_LST <<<<\n", line);
		tokenlstiter(lst, print_node);
		#endif
		/* ADD EXPANSION FUNC ? */
		/* ADD PARSER */
		/* ADD EVALUATOR */
		/* ADD AST DEL */
		tokenlstdel(&lst);
		ft_strdel(&line);
		ft_putendl("");
	}
	return (FUNCT_SUCCESS);
}
