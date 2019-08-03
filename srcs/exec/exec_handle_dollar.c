/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_handle_dollar.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/14 01:05:00 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/03 11:15:18 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	return_error(int ret, int error)
{
	if (error == E_ALLOC)
		ft_eprintf("vsh: failed to allocate enough memory\n");
	return (ret);
}

/*
**	Goal of the function is to take the expansion sequence and
**	replace it with the value of the parameter.
*/

static int	repl_regular_var(char **value, char *replace_str,
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
		return (return_error(FUNCT_ERROR, E_ALLOC));
	ft_strncpy(new, *value, start);
	if (replace_str != NULL)
		ft_strcat(new, replace_str);
	ft_strcat(new, &(*value)[start + len]);
	ft_strdel(value);
	*value = new;
	return (FUNCT_SUCCESS);
}

/*
**	Goal of this function is to extract the identifier
**	and get its value (or nothing if it doesn't exist)
*/

int			exec_handle_dollar(char **value, int *i, t_envlst *envlst)
{
	int		i_dollar;
	char	*replace_str;
	char	*identifier;

	if ((*value)[*i + 1] == '{')
		return (exec_handle_bracketed_var(value, i, envlst));
	i_dollar = *i;
	(*i)++;
	while (tools_isidentifierchar((*value)[*i]) == true)
		(*i)++;
	if (*i == i_dollar + 1)
		return (FUNCT_FAILURE);
	identifier = ft_strndup(&(*value)[i_dollar + 1], *i - (i_dollar + 1));
	if (identifier == NULL)
		return (return_error(FUNCT_ERROR, E_ALLOC));
	replace_str = env_getvalue(identifier, envlst);
	ft_strdel(&identifier);
	if (repl_regular_var(value, replace_str, i_dollar, *i - i_dollar)
		== FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (replace_str != NULL)
		i_dollar += ft_strlen(replace_str);
	*i = i_dollar;
	return (FUNCT_SUCCESS);
}
