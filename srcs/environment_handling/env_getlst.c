/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_getlst.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/04 08:06:54 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/06/13 16:06:46 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

t_envlst	*env_getlst(void)
{
	t_envlst	*envlst;
	t_envlst	*new;
	extern char	**environ;
	int			i;

	i = 0;
	envlst = NULL;
	while (environ[i] != NULL)
	{
		new = env_lstnew(environ[i], ENV_EXTERN);
		if (new == NULL)
		{
			env_lstdel(&envlst);
			return (NULL);
		}
		env_lstaddback(&envlst, new);
		i++;
	}
	return (envlst);
}
