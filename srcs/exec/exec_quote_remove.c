/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_quote_remove.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/13 11:20:18 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/07 13:47:02 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Performs quote removal on all the WORD and ASSIGN tokens from the
**	HEAD `t_ast *node` and downwards.
**
**	A special case is added for heredocs:
**	Heredocs will not do any quote removal besides '\' and only if the
**	HEREDOC_DELIMITER does not contain any quoting (i.e. T_FLAG_HEREDOC_NOEXP
**	not true).
*/

void		exec_quote_remove(t_ast *node)
{
	char	*str;
	bool	is_heredoc;

	if (node->left != NULL)
		exec_quote_remove(node->left);
	if (node->right != NULL)
		exec_quote_remove(node->right);
	if ((node->type == WORD || node->type == ASSIGN)
	&& (node->flags & T_FLAG_HEREDOC_NOEXP) == false
	&& node->is_expanded == false)
	{
		is_heredoc = false;
		if (node->flags & T_FLAG_ISHEREDOC)
			is_heredoc = true;
		str = node->value;
		if (node->type == ASSIGN)
			str = ft_strchr(str, '=');
		tools_remove_quotes_etc(str, is_heredoc);
	}
}
