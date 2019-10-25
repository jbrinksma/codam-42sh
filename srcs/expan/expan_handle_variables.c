/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expan_handle_variables.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/07 20:54:47 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/23 18:40:25 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Finds unquoted and unescaped '$', then checks if
**	it is a bracketed parameter/variable or not,
**	and then executes the proper functions on it.
**
**	Notice the '&i' gets sent with these functions, because
**	when it is done, it will point to the characted after
**	the var with which the $PARAM was just replaced. (to avoid
**	faulty param replacement).
*/

static void	update_quote_status(char c, int *i, char *quote)
{
	if (*quote == '\0')
		*quote = c;
	else if (c == *quote)
		*quote = '\0';
	(*i)++;
}

static int	scan_value(t_ast *node, t_envlst *envlst)
{
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	while (node->value[i] != '\0')
	{
		if (node->value[i] == '\\' && quote != '\'')
			i += 2;
		else if (node->value[i] == '\'' || node->value[i] == '\"')
			update_quote_status(node->value[i], &i, &quote);
		else if (node->value[i] == '$' && quote != '\'')
		{
			if (expan_handle_dollar(&node->value, &i, envlst) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		else if (node->value[i] == '~')
		{
			if (expan_tilde_expansion(node, &i) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		else
			i++;
	}
	return (FUNCT_SUCCESS);
}

int			expan_handle_variables(t_ast *node, t_envlst *envlst)
{
	if (node == NULL)
		return (FUNCT_FAILURE);
	if (expan_handle_variables(node->right, envlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (expan_handle_variables(node->left, envlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if ((node->type == WORD || node->type == ASSIGN)
		&& node->flags & T_FLAG_HASSPECIAL
		&& (node->flags & T_FLAG_HEREDOC_NOEXP) == false)
	{
		if (scan_value(node, envlst) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}
