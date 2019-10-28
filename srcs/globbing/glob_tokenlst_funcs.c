/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_tokenlst_funcs.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/21 11:27:35 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/22 11:31:35 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		glob_deltoken(t_globtoken **token)
{
	ft_strdel(&(*token)->word_chunk);
	ft_memdel((void**)token);
}

void		glob_del_tokenlst(t_globtoken **token)
{
	if (*token == NULL)
		return ;
	glob_del_tokenlst(&(*token)->next);
	glob_deltoken(token);
}

t_globtoken	*glob_tokenlstnew(char *word_chunk, int type)
{
	t_globtoken	*globtoken;

	if (word_chunk == NULL)
		return (NULL);
	globtoken = (t_globtoken*)ft_memalloc(sizeof(t_globtoken));
	if (globtoken == NULL)
		return (NULL);
	globtoken->word_chunk = word_chunk;
	if (globtoken->word_chunk == NULL)
	{
		ft_memdel((void*)&globtoken);
		return (NULL);
	}
	globtoken->tk_type = type;
	globtoken->word_len = ft_strlen(globtoken->word_chunk);
	return (globtoken);
}

void		glob_tokenlstadd(t_globtoken **lst, t_globtoken *new)
{
	t_globtoken *probe;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	probe = *lst;
	while (probe->next != NULL)
		probe = probe->next;
	probe->next = new;
}
