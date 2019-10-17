/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_to_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 15:25:10 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/17 15:53:43 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

/*
** Write the history to file
*/

static void	history_print_to_fd(int fd, t_datahistory *history)
{
	t_historyitem *probe;

	probe = history->head;
	while (probe != NULL)
	{
		ft_dprintf(fd, "%s%c", probe->str, HIST_SEPARATE);
		probe = probe->next;
	}
}

int			history_to_file(t_datahistory *history)
{
	int		fd;
	char	*histfile;

	if (history->head == NULL)
		return (FUNCT_ERROR);
	histfile = history_get_filename();
	if (histfile == NULL)
		return (FUNCT_ERROR);
	fd = open(histfile, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_eprintf(E_HIST_OPEN_STR);
		ft_strdel(&histfile);
		return (FUNCT_ERROR);
	}
	history_print_to_fd(fd, history);
	close(fd);
	ft_strdel(&histfile);
	return (FUNCT_SUCCESS);
}
