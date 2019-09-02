/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/25 17:24:39 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/29 13:26:15 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static bool	is_cmd_seperator(t_tokens type)
{
	return (type == PIPE || type == AND_IF || type == OR_IF || type == BG ||
		type == SEMICOL || type == NEWLINE);
}

static bool	alias_space_check(char *alias)
{
	char c;

	c = alias[ft_strlen(alias) - 1];
	return (c == '\t' || c == ' ');
}

static char	*alias_find_value(char *key, t_aliaslst *aliaslst, char **expanded)
{
	int		key_len;
	int		i;

	if (expanded != NULL)
	{
		i = 0;
		while (expanded[i] != NULL)
		{
			if (ft_strequ(expanded[i], key) == true)
				return (NULL);
			i++;
		}
	}
	key_len = ft_strlen(key);
	while (aliaslst != NULL)
	{
		if (ft_strnequ(key, aliaslst->var, key_len) == true &&
			(aliaslst->var[key_len] == '='))
			return (aliaslst->var);
		aliaslst = aliaslst->next;
	}
	return (NULL);
}

int			alias_expansion_checker(t_vshdata *data, t_tokenlst *probe,
			char **expanded)
{
	t_tokenlst	*new_probe;
	char		*alias;

	alias = alias_find_value(probe->next->value, data->alias->aliaslst, expanded);
	if (alias != NULL)
	{
		if (alias_space_check(alias) == true)
		{
			if (alias_expansion(data, &probe->next, expanded) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		else
		{
			new_probe = probe;
			while (new_probe->next->type != END &&
				is_cmd_seperator(new_probe->next->type) == false)
				new_probe = new_probe->next;
			if (alias_expansion(data, &new_probe, expanded) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		if (alias_replace(data, probe, alias, expanded) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}

int			alias_expansion(t_vshdata *data, t_tokenlst **tokenlst,
			char **expanded)
{
	t_tokenlst	*probe;
	int			ret;

	probe = *tokenlst;
	while (probe->type != END && probe->next->type != END)
	{
		if (probe->next->type == WORD &&
			(probe->flags & T_FLAG_HASSPECIAL) == false)
		{
			ret = alias_expansion_checker(data, probe, expanded);
			if (ret != FUNCT_FAILURE)
				return (ret);
		}
		while (probe->next->type != END &&
			is_cmd_seperator(probe->next->type) == false)
			probe = probe->next;
		probe = probe->next;
	}
	return (FUNCT_SUCCESS);
}
