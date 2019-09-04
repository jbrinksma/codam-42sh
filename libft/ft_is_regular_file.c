/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_regular_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/04 12:11:41 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/04 11:14:54 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

int		ft_is_regular_file(const char *path)
{
	struct stat stat_path;

	if (lstat(path, &stat_path) == -1)
		return (-1);
	return (S_ISREG(stat_path.st_mode));
}
