/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expan_tilde_expansion.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/02 13:50:51 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/23 18:42:25 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	A ~ or ~/ will be expanded to HOME or HOME/ respectively.
**	Any characters after ~ not begin a slash are seen as an username
**	(or in case of a an assign, paths can also be split by a colon)
**	~ will now be replaced with the HOME of username
**	expan_get_home_path will search for this user and return it's dir path
**	when the user is not found, an error is returned and the cmd is not executed
*/

#include "vsh.h"
#include <sys/types.h>
#include <pwd.h>

static char	*expan_get_login(t_ast *node, int i)
{
	int		login_len;
	char	colon;

	colon = '\0';
	login_len = 0;
	if (node->type == ASSIGN)
		colon = ':';
	i++;
	while (node->value[i] != '\0' && node->value[i] != colon &&
		node->value[i] != '/')
	{
		i++;
		login_len++;
	}
	if (login_len == 0)
		return (ft_strnew(0));
	else
		return (ft_strsub(node->value, i - login_len, login_len));
}

static int	expan_get_home_path(char *login, char **home_path)
{
	struct passwd *user_info;

	if (login[0] == '\0')
	{
		*home_path = getenv("HOME");
		if (home_path == NULL)
			return (err_ret_prog_exit(E_N_FAIL_HOME, "tilde", EXIT_FAILURE));
	}
	else
	{
		user_info = getpwnam(login);
		if (user_info == NULL)
			return (err_ret_prog_exit(E_INVALID_USER, login, EXIT_FAILURE));
		*home_path = user_info->pw_dir;
	}
	return (FUNCT_SUCCESS);
}

static int	expan_add_home_path(t_ast *node, int *i, char *home_path,
			int login_len)
{
	char	*new_value;
	int		len_home;

	len_home = ft_strlen(home_path);
	new_value = ft_strnew(len_home - login_len + ft_strlen(node->value));
	if (new_value == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	ft_strncpy(new_value, node->value, *i);
	ft_strcat(&new_value[*i], home_path);
	ft_strcat(new_value, &node->value[*i + login_len + 1]);
	*i += len_home;
	ft_strdel(&node->value);
	node->value = new_value;
	return (FUNCT_SUCCESS);
}

int			expan_tilde_expansion(t_ast *node, int *i)
{
	char	*login;
	char	*home_path;
	int		ret;

	home_path = NULL;
	if ((node->type == WORD && *i == 0) || (node->type == ASSIGN && (*i == 0 ||
		(node->value[*i - 1] == ':' || node->value[*i - 1] == '='))))
	{
		login = expan_get_login(node, *i);
		if (login == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
		if (expan_get_home_path(login, &home_path) == FUNCT_ERROR)
		{
			ft_strdel(&login);
			return (FUNCT_ERROR);
		}
		ret = expan_add_home_path(node, i, home_path, ft_strlen(login));
		ft_strdel(&login);
		return (ret);
	}
	else
		*i += 1;
	return (FUNCT_FAILURE);
}
