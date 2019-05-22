/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 10:23:43 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/22 10:56:56 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	tokenlstdel(t_tokenlst **token_lst)
{
	if (*token_lst == NULL)
		return ;
	if ((*token_lst)->next != NULL)
		tokenlstdel(&(*token_lst)->next);
	if ((*token_lst)->type == WORD || (*token_lst)->type == ASSIGN)
		ft_strdel(&(*token_lst)->value);
	ft_memdel((void**)token_lst);
}

int		lexer_error(t_tokenlst **token_lst)
{
	if (*token_lst != NULL)
		tokenlstdel(token_lst);
	ft_putstr_fd("vsh: lexer: malloc error\n", STDERR_FILENO);
	return (FUNCT_ERROR);
}

void	change_state(t_scanner *scanner, void (*state_x)(t_scanner *scanner))
{
	(scanner->str_index)++;
	(scanner->tk_len)++;
	state_x(scanner);
}
