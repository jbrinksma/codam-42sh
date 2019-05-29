/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_del_ast.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/26 12:21:49 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/27 15:47:42 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

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
