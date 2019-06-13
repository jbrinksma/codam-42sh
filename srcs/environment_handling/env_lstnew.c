/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstnew.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 18:35:25 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/06/07 18:36:52 by jbrinksm      ########   odam.nl         */
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
