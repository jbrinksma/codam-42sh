/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 10:23:43 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/27 16:56:33 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	lexer_tokenlstdel(t_tokenlst **token_lst)
{
	if (*token_lst == NULL)
		return ;
	if ((*token_lst)->next != NULL)
		lexer_tokenlstdel(&(*token_lst)->next);
	if ((*token_lst)->type == WORD || (*token_lst)->type == ASSIGN
		|| (*token_lst)->type == IO_NUMBER)
		ft_strdel(&(*token_lst)->value);
	ft_memdel((void**)token_lst);
}

int		lexer_error(t_tokenlst **token_lst)
{
	if (*token_lst != NULL)
		lexer_tokenlstdel(token_lst);
	ft_putstr_fd("vsh: lexer: malloc error\n", STDERR_FILENO);
	return (FUNCT_ERROR);
}

void	lexer_change_state(t_scanner *scanner,
		void (*lexer_state_x)(t_scanner *scanner))
{
	(scanner->str_index)++;
	(scanner->tk_len)++;
	lexer_state_x(scanner);
}

bool	lexer_is_shellspec(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ';' || c == '\n')
		return (true);
	return (false);
}
