/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_line_to_file.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 15:25:10 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/31 15:18:54 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <fcntl.h>
#include <unistd.h>

int		history_line_to_file(char *line)
{
	int	fd;

	fd = open("/tmp/.vsh_history",
		O_APPEND | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf("Cannot open/create vsh history file \n");
		return (FUNCT_ERROR);
	}
	ft_putendl_fd(line, fd);
	close(fd);
	return (FUNCT_SUCCESS);
}
