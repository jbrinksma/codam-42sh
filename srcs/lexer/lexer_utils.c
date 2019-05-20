/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 10:23:43 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/19 16:00:41 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		add_tk_to_lst(t_list **lst, t_token *token)
{
	t_list *new;

	new = ft_lstnew(token, sizeof(t_token));
	if (new == NULL)
	{
		token->type = ERROR;
		return (FUNCT_ERROR);
	}
	ft_lstaddback(*lst, new);
	return (FUNCT_SUCCESS);
}

void	del_tk_node(void *content, size_t size)
{
	if (((t_token*)content)->type == WORD ||
		((t_token*)content)->type == ASSIGN)
		ft_strdel(&((t_token*)content)->value.str);
	ft_bzero(content, size);
	ft_memdel(&content);
}

int		lexer_error(t_list **token_lst)
{
	if (*token_lst != NULL)
		ft_lstdel(token_lst, del_tk_node);
	ft_putstr_fd("vsh: lexer: malloc error\n", STDERR_FILENO);
	return (FUNCT_ERROR);
}

void	change_state(t_scanner *scanner, void (*state_x)(t_scanner *scanner))
{
	(scanner->str_index)++;
	(scanner->tk_len)++;
	state_x(scanner);
}
