/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_handle_variables.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/07 20:54:47 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/03 11:10:34 by jbrinksm      ########   odam.nl         */
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
	char	**value;

	value = &node->value;
	i = 0;
	quote = '\0';
	if (exec_tilde_expansion(node, &i) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	while ((*value)[i] != '\0')
	{
		if ((*value)[i] == '\\' && quote != '\'')
			i += 2;
		else if ((*value)[i] == '\'' || (*value)[i] == '\"')
			update_quote_status((*value)[i], &i, &quote);
		else if ((*value)[i] == '$' && quote != '\'')
		{
			if (exec_handle_dollar(value, &i, envlst) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		else
			i++;
	}
	return (FUNCT_SUCCESS);
}

int			exec_handle_variables(t_ast *node, t_envlst *envlst)
{
	if (node == NULL)
		return (FUNCT_FAILURE);
	if (exec_handle_variables(node->sibling, envlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (exec_handle_variables(node->child, envlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if ((node->type == WORD || node->type == ASSIGN) &&
		node->flags & T_FLAG_HASSPECIAL)
	{
		if (scan_value(node, envlst) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}
