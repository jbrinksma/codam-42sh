/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_matchlst_funcs.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 19:53:46 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/06 13:33:53 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void					glob_delmatch(t_globmatchlst **match)
{
	ft_strdel(&(*match)->word);
	ft_memdel((void**)match);
}

void					glob_del_matchlst(t_globmatchlst **matchlst)
{
	if (*matchlst == NULL)
		return ;
	glob_del_matchlst(&(*matchlst)->next);
	glob_delmatch(matchlst);
}

static t_globmatchlst	*glob_match_lst_new(char *item)
{
	t_globmatchlst *new;

	new = (t_globmatchlst*)ft_memalloc(sizeof(t_globmatchlst));
	if (new == NULL)
		return (NULL);
	new->word = ft_strdup(item);
	if (new->word == NULL)
		return (NULL);
	new->word_len = ft_strlen(new->word);
	return (new);
}

int						glob_match_lst_add(t_globmatchlst **lst, char *word)
{
	t_globmatchlst	*new;

	if (lst == NULL || word == NULL)
		return (FUNCT_ERROR);
	new = glob_match_lst_new(word);
	if (new == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	if (*lst == NULL)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
	return (FUNCT_SUCCESS);
}
