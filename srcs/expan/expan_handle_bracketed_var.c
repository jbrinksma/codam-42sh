/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expan_handle_bracketed_var.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/14 01:02:46 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/05 16:43:37 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Goal of the function is to take the expansion sequence and
**	replace it with the value of the parameter.
*/

int			expan_var_error_print(char *str, int len)
{
	ft_eprintf(E_P_BAD_SUBS, len, str);
	g_state->exit_code = EXIT_WRONG_USE;
	return (FUNCT_ERROR);
}

static int	repl_bracketed_var(char **value, char *replace_str,
			int start, int len)
{
	char	*new;
	int		val_len;

	if (replace_str != NULL)
		val_len = ft_strlen(replace_str);
	else
		val_len = 0;
	new = ft_strnew(ft_strlen(*value) - len + val_len);
	if (new == NULL)
		return (FUNCT_FAILURE);
	ft_strncpy(new, *value, start);
	if (replace_str != NULL)
		ft_strcat(new, replace_str);
	if ((*value)[start + len] == '}')
		ft_strcat(new, &(*value)[start + len + 1]);
	else
		ft_strcat(new, &(*value)[start + len]);
	ft_strdel(value);
	*value = new;
	return (FUNCT_SUCCESS);
}

/*
**	Goal of this function is to extract the identifier
**	and get its value (or nothing if it doesn't exist)
*/

int			expan_handle_bracketed_var(char **value, int *i, t_envlst *envlst)
{
	int		i_dollar;
	char	*identifier;
	char	*replace_str;

	i_dollar = *i;
	*i += 2;
	while (tools_isidentifierchar((*value)[*i]) == true)
		(*i)++;
	if ((*value)[*i] != '}' || *i == i_dollar + 2)
		return (expan_var_error_print(&(*value)[i_dollar], (*i - i_dollar) + 1));
	identifier = ft_strndup(&(*value)[i_dollar + 2], *i - (i_dollar + 2));
	if (identifier == NULL)
		return (FUNCT_ERROR);
	replace_str = env_getvalue(identifier, envlst);
	ft_strdel(&identifier);
	if (repl_bracketed_var(value, replace_str, i_dollar, *i - i_dollar)
		== FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (replace_str != NULL)
		i_dollar += ft_strlen(replace_str);
	*i = i_dollar;
	return (FUNCT_SUCCESS);
}
