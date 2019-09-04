/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdir.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 12:51:00 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/04 11:14:37 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

int		ft_isdir(const char *path)
{
	struct stat stat_path;

	if (stat(path, &stat_path) == -1)
		return (-1);
	return (S_ISDIR(stat_path.st_mode));
}
