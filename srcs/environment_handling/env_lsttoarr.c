/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lsttoarr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/04 10:54:56 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/06 11:05:07 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		env_lstlen(t_envlst *lst)
{
	t_envlst	*probe;
	int			len;

	probe = lst;
	len = 0;
	while (probe != NULL)
	{
		if (probe->type & (ENV_EXTERN | ENV_TEMP))
			len++;
		probe = probe->next;
	}
	return (len);
}

char	**env_lsttoarr(t_envlst *lst)
{
	char		**vshenviron;
	t_envlst	*probe;
	int			len;
	int			i;

	len = env_lstlen(lst);
	vshenviron = (char**)ft_memalloc(sizeof(char*) * (len + 1));
	if (vshenviron == NULL)
		return (NULL);
	i = 0;
	probe = lst;
	while (i < len)
	{
		if (probe->type & (ENV_EXTERN | ENV_TEMP))
		{
			vshenviron[i] = probe->var;
			i++;
		}
		probe = probe->next;
	}
	return (vshenviron);
}
