/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/19 11:23:37 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/19 11:42:49 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	hash_init(t_vshdata *vshdata)
{
	int i;

	i = 0;
	while (i < HT_SIZE)
	{
		vshdata->ht[i] = NULL;
		i++;
	}
	vshdata->ht_flag = HT_EMPTY;
}
