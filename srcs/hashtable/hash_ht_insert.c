/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash_ht_insert.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/18 15:18:11 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/26 18:40:20 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
** hash_create_hash uses djb2 by Dan Bernstein
*/

unsigned int	hash_create_hash(char *key)
{
	unsigned long hash;

	hash = 5381;
	while (*key != '\0')
	{
		hash = (hash * 33) ^ *key;
		key++;
	}
	hash = hash % HT_SIZE;
	return ((unsigned int)hash);
}

static int		hash_new(t_ht **ht, char *key, char *path, int hit)
{
	t_ht *new;

	new = (t_ht*)ft_memalloc(sizeof(t_ht));
	if (new == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	new->key = ft_strdup(key);
	if (new->key == NULL)
	{
		free(new);
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	}
	new->path = path;
	new->hits = hit;
	*ht = new;
	return (FUNCT_SUCCESS);
}

static int		hash_exist(t_ht *ht, char *path, int hit)
{
	if (hit == HASH_HIT)
		ht->hits += hit;
	else
		ht->hits = hit;
	ft_strdel(&ht->path);
	ht->path = path;
	return (FUNCT_SUCCESS);
}

int				hash_ht_insert(t_vshdata *data,
				char *key, char *path, int hit)
{
	unsigned int	hash;
	t_ht			*probe;

	hash = hash_create_hash(key);
	data->hashtable->ht_flag = HT_HAS_CONTENT;
	if (data->hashtable->ht[hash] == NULL)
		return (hash_new(&data->hashtable->ht[hash], key, path, hit));
	else
	{
		probe = data->hashtable->ht[hash];
		while (probe != NULL)
		{
			if (ft_strequ(probe->key, key) == true)
				return (hash_exist(probe, path, hit));
			if (probe->next == NULL)
				break ;
			probe = probe->next;
		}
		return (hash_new(&probe->next, key, path, hit));
	}
}
