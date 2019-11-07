/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init_files.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/27 12:39:59 by omulder        #+#    #+#                */
/*   Updated: 2019/11/04 12:56:49 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <pwd.h>

int		shell_init_files(t_vshdata *data)
{
	char			*homedir;
	struct passwd	*pw;

	homedir = env_getvalue("HOME", data->envlst);
	if (homedir == NULL)
	{
		pw = getpwuid(getuid());
		if (pw == NULL)
			return (err_ret(E_FAIL_HOME));
		homedir = pw->pw_dir;
	}
	data->alias->alias_file =
	ft_strjoinfree_s2(homedir, ft_strjoin("/", ALIASFILENAME));
	if (data->alias->alias_file == NULL)
		return (err_ret(E_ALLOC_STR));
	return (FUNCT_SUCCESS);
}
