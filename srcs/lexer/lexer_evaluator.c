/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_evaluator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/18 19:03:52 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/27 16:49:32 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	The lexer_evaluator removes '\', '\'' and '"' from token WORD and ASSIGN.
*/

static void	trim_backwardslash(char *str, int *i_new, int *i)
{
	if (str[*i] == '\\' && str[*i + 1] == '\\')
	{
		str[*i_new] = str[*i];
		(*i_new)++;
		(*i) += 2;
	}
	else
		(*i)++;
}

static void	trim_double_qoutes(char *str, int *i_new, int *i)
{
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '\\' && str[*i + 1] == '"')
		{
			(*i)++;
			str[*i_new] = str[*i];
			(*i_new)++;
			(*i)++;
		}
		else if (str[*i] == '\\')
			trim_backwardslash(str, i_new, i);
		else
		{
			str[*i_new] = str[*i];
			(*i_new)++;
			(*i)++;
		}
	}
	(*i)++;
}

static void	trim_single_qoutes(char *str, int *i_new, int *i)
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

static void	trim_word(char *str)
{
	int		i;
	int		i_new;

	i = 0;
	i_new = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			trim_single_qoutes(str, &i_new, &i);
		else if (str[i] == '"')
			trim_double_qoutes(str, &i_new, &i);
		else if (str[i] == '\\')
			trim_backwardslash(str, &i_new, &i);
		else
		{
			str[i_new] = str[i];
			i_new++;
			i++;
		}
	}
	ft_bzero(&str[i_new], i - i_new);
}

void		lexer_evaluator(t_tokenlst *token_lst)
{
	while (token_lst)
	{
		if (token_lst->type == WORD || token_lst->type == ASSIGN)
			trim_word(token_lst->value);
		token_lst = token_lst->next;
	}
}
