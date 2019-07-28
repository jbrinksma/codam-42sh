/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_to_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 15:25:10 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/28 18:16:45 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

/*
** Write the history to file
*/

int		history_to_file(t_vshdata *vshdata)
{
	int		fd;
	int		i;

	if (vshdata->history == NULL || vshdata->history_file == NULL)
		return (FUNCT_ERROR);
	fd = open(vshdata->history_file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_putstr_fd("Cannot open/create vsh history file \n", STDERR_FILENO);
		return (FUNCT_ERROR);
	}
	i = 0;
	while (i < HISTORY_MAX && vshdata->history[i]->str != NULL)
	{
		ft_dprintf(fd, "%s%c", vshdata->history[i]->str, '\n');
		i++;
	}
	close(fd);
	return (FUNCT_SUCCESS);
}
