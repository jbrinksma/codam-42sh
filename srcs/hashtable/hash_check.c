/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/19 12:05:52 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/26 18:40:20 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static char	*check_lst(t_ht *ht_lst, char *key)
{
	while (ht_lst != NULL)
	{
		if (ft_strequ(key, ht_lst->key) == true)
		{
			ht_lst->hits += 1;
			return (ht_lst->path);
		}
		ht_lst = ht_lst->next;
	}
	return (NULL);
}

int			hash_check(t_vshdata *data, char *key, char **binary)
{
	int		hash;
	char	*bin_dup;

	hash = hash_create_hash(key);
	if (data->hashtable->ht[hash] == NULL)
		return (FUNCT_FAILURE);
	bin_dup = check_lst(data->hashtable->ht[hash], key);
	if (bin_dup == NULL)
		return (FUNCT_FAILURE);
	*binary = ft_strdup(bin_dup);
	if (*binary == NULL)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
