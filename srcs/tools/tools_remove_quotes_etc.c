/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_remove_quotes_etc.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 16:31:09 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/11 16:31:44 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	remove_backslash(char *str, int *i, int *i_new)
{
	(*i)++;
	if (str[(*i)] == '\0')
		return ;
	str[*i_new] = str[*i];
	(*i)++;
	(*i_new)++;
}

/*
**	In a expandable heredoc we only want to escape '\', '$', and
**	handle the special line continuation (escaped '\n').
*/

static void	remove_heredoc_backslash(char *str, int *i, int *i_new)
{
	(*i)++;
	if (str[*i] == '\\' || str[*i] == '$')
	{
		str[*i_new] = str[*i];
		(*i_new)++;
		(*i)++;
	}
	else if (str[*i] == '\n')
		(*i)++;
	else
		(*i)--;
}

static void	remove_double_quote(char *str, int *i, int *i_new)
{
	(*i)++;
	while (str[*i] != '"' && str[*i] != '\0')
	{
		if (str[*i] == '\\' && ft_strchr("\"\\$", str[(*i) + 1]) != NULL)
			remove_backslash(str, i, i_new);
		else
		{
			str[*i_new] = str[*i];
			(*i_new)++;
			(*i)++;
		}
	}
	if (str[*i] == '"')
		(*i)++;
}

static void	remove_single_quote(char *str, int *i, int *i_new)
{
	(*i)++;
	while (str[*i] != '\'' && str[*i] != '\0')
	{
		str[*i_new] = str[*i];
		(*i_new)++;
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++;
}

/*
**	Iterates through the whole string and removes any quoting characters that
**	are still present. If the string is a heredoc, limited measures will be
**	taken.
*/

void	tools_remove_quotes_etc(char *str, bool is_heredoc)
{
	int		i;
	int		i_new;

	i = 0;
	i_new = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && is_heredoc == false)
			remove_backslash(str, &i, &i_new);
		else if (str[i] == '\\' && is_heredoc == true)
			remove_heredoc_backslash(str, &i, &i_new);
		else if (str[i] == '\'' && is_heredoc == false)
			remove_single_quote(str, &i, &i_new);
		else if (str[i] == '"' && is_heredoc == false)
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
