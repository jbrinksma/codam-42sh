/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_astdel.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/26 12:21:49 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/05 13:21:34 by mavan-he      ########   odam.nl         */
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
	if ((*ast)->left != NULL)
		parser_astdel(&(*ast)->left);
	if ((*ast)->right != NULL)
		parser_astdel(&(*ast)->right);
	ft_strdel(&(*ast)->value);
	ft_memdel((void**)ast);
}
