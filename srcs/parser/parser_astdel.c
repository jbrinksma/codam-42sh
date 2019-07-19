/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_astdel.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/26 12:21:49 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/16 14:47:15 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	parser_return_del(t_ast **ast)
{
	parser_astdel(ast);
	return (false);
}

void	parser_astdel(t_ast **ast)
{
	if (ast == NULL || *ast == NULL)
		return ;
	if ((*ast)->child != NULL)
		parser_astdel(&(*ast)->child);
	if ((*ast)->sibling != NULL)
		parser_astdel(&(*ast)->sibling);
	ft_strdel(&(*ast)->value);
	ft_memdel((void**)ast);
}
