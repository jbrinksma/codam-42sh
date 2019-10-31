/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init_features.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/04 10:25:31 by rkuijper       #+#    #+#                */
/*   Updated: 2019/09/04 11:44:55 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

t_datahashtable	*shell_init_vshdatahashtable(void)
{
	t_datahashtable	*hashtable;

	hashtable = ft_memalloc(sizeof(t_datahashtable));
	if (hashtable == NULL)
		return (NULL);
	return (hashtable);
}

t_datahistory	*shell_init_vshdatahistory(void)
{
	t_datahistory	*history;

	history = ft_memalloc(sizeof(t_datahistory));
	if (history == NULL)
		return (NULL);
	return (history);
}

t_dataalias		*shell_init_vshdataalias(void)
{
	t_dataalias	*alias;

	alias = ft_memalloc(sizeof(t_dataalias));
	if (alias == NULL)
		return (NULL);
	alias->alias_file = ALIASFILENAME;
	return (alias);
}

t_datajobs		*shell_init_vshdatajobs(void)
{
	t_datajobs	*jobs;

	jobs = ft_memalloc(sizeof(t_datajobs));
	if (jobs == NULL)
		return (NULL);
	return (jobs);
}
