/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_quote_remove.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/13 11:20:18 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/15 11:59:39 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	remove_backslash(char *str, int *i, int *i_new)
{
	(*i)++;
	str[*i_new] = str[*i];
	(*i)++;
	(*i_new)++;
}

static void	remove_double_quote(char *str, int *i, int *i_new)
{
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '\\' && ft_strchr("\"\\$", str[(*i) + 1]))
			remove_backslash(str, i, i_new);
		else
		{
			str[*i_new] = str[*i];
			(*i_new)++;
			(*i)++;
		}
	}
	(*i)++;
}

static void	remove_single_quote(char *str, int *i, int *i_new)
{
	(*i)++;
	while (str[*i] != '\'')
	{
		str[*i_new] = str[*i];
		(*i_new)++;
		(*i)++;
	}
	(*i)++;
}

static void	remove_quotes_etc(char *str)
{
	int		i;
	int		i_new;

	i = 0;
	i_new = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
			remove_backslash(str, &i, &i_new);
		else if (str[i] == '\'')
			remove_single_quote(str, &i, &i_new);
		else if (str[i] == '"')
			remove_double_quote(str, &i, &i_new);
		else
		{
			str[i_new] = str[i];
			i++;
			i_new++;
		}
	}
	ft_bzero(&str[i_new], i - i_new);
}

void		exec_quote_remove(t_ast *node)
{
	char *str;

	if (node->child != NULL)
		exec_quote_remove(node->child);
	if (node->sibling != NULL)
		exec_quote_remove(node->sibling);
	if (node->type == WORD || node->type == ASSIGN)
	{
		str = node->value;
		if (node->type == ASSIGN)
		{
			while (str[0] != '=')
				str++;
			str++;
		}
		remove_quotes_etc(str);
	}
}
