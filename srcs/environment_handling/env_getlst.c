/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_getlst.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/04 08:06:54 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/06 13:39:51 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <pwd.h>

static int		env_add_to_list(char *str, t_envlst **new)
{
	int type;

	type = ENV_EXTERN;
	if (tools_check_for_special(str) == true)
		type |= ENV_SPECIAL;
	*new = env_lstnew(str, type);
	if (*new == NULL)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

static int		env_set_home(t_vshdata *data)
{
	char			*homedir;
	struct passwd	*pw;
	t_envlst		*new;

	new = NULL;
	homedir = env_getvalue("HOME", data->envlst);
	if (homedir != NULL)
		return (FUNCT_SUCCESS);
	pw = getpwuid(getuid());
	if (pw == NULL)
		return (err_ret(E_FAIL_HOME));
	homedir = pw->pw_dir;
	homedir = ft_strjoin("HOME=", homedir);
	if (homedir == NULL || env_add_to_list(homedir, &new) == FUNCT_ERROR)
		return (err_ret(E_ALLOC_STR));
	env_lstadd_to_sortlst(data->envlst, new);
	return (FUNCT_SUCCESS);
}

t_envlst		*env_getlst(void)
{
	t_envlst	*envlst;
	t_envlst	*new;
	extern char	**environ;
	int			i;

	i = 0;
	envlst = env_lstnew("*HEAD*", ENV_HEAD);
	if (envlst == NULL)
		return (NULL);
	while (environ[i] != NULL)
	{
		if (env_add_to_list(environ[i], &new) == FUNCT_ERROR)
		{
			env_lstdel(&envlst);
			return (NULL);
		}
		env_lstaddback(&envlst, new);
		i++;
	}
	env_sort(envlst);
	return (envlst);
}

int				env_init_envlst(t_vshdata *vshdata)
{
	vshdata->envlst = env_getlst();
	if (vshdata->envlst == NULL)
		return (err_ret(E_ALLOC_STR));
	if (env_set_home(vshdata) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
