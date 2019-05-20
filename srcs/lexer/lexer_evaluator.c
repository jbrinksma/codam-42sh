/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_evaluator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/18 19:03:52 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/20 13:57:34 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	The evaluator removes '\', '\'' and '"' from token WORD and ASSIGN.
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

void		evaluator(t_list *token_lst)
{
	while (token_lst)
	{
		if (((t_token*)token_lst->content)->type == WORD ||
			((t_token*)token_lst->content)->type == ASSIGN)
			trim_word(((t_token*)token_lst->content)->value.str);
		token_lst = token_lst->next;
	}
}
