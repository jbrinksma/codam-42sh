/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash_print.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/18 17:30:34 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/18 17:40:08 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	hash_print_line(t_ht *node)
{
	if (node == NULL)
		return ;
	ft_printf("%4d     %s\n", node->hits, node->path);
	hash_print_line(node->next);
}

void		hash_print(t_ht **ht)
{
	int		i;

	i = 0;
	ft_printf("hits     command\n");
	while (i < HT_SIZE)
	{
		if (ht[i] != NULL)
			hash_print_line(ht[i]);
		i++;
	}
}
