/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_getlst.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/04 08:06:54 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/06/04 11:42:12 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

t_envlst	*env_lstnew(char *var, unsigned char type)
{
	t_envlst	*new;

	if (var == NULL)
		return (NULL);
	new = (t_envlst*)ft_memalloc(sizeof(t_envlst));
	if (new == NULL)
		return (NULL);
	new->var = ft_strdup(var);
	if (new->var == NULL)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

void		env_lstaddback(t_envlst **lst, t_envlst *new)
{
	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else if ((*lst)->next == NULL)
		(*lst)->next = new;
	else
		env_lstaddback(&(*lst)->next, new);
}

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
			/* free list */
			return (NULL);
		}
		env_lstaddback(&envlst, new);
		i++;
	}
	return (envlst);
}