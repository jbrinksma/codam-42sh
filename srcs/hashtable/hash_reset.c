/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash_reset.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/19 10:39:06 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/19 11:41:35 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	del_hash_lst(t_ht *del)
{
	if (del == NULL)
		return ;
	del_hash_lst(del->next);
	ft_strdel(&del->key);
	ft_strdel(&del->path);
	ft_memdel((void**)&del);
}

void		hash_reset(t_vshdata *vshdata)
{
	int i;

	i = 0;
	while (i < HT_SIZE)
	{
		if (vshdata->ht[i] != NULL)
		{
			del_hash_lst(vshdata->ht[i]);
			vshdata->ht[i] = NULL;
		}
		i++;
	}
	vshdata->ht_flag = HT_EMPTY;
}
