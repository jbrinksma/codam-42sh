/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_to_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 15:25:10 by mavan-he       #+#    #+#                */
/*   Updated: 2019/06/02 10:37:20 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "vsh_history.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int		history_to_file(void)
{
	int		fd;
	int		i;

	fd = open("/tmp/.vsh_history",
		O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_putstr_fd("Cannot open/create vsh history file \n", STDERR_FILENO);
		return (FUNCT_ERROR);
	}
	i = 0;
	while (history[i] != NULL)
	{
		ft_putendl_fd(history[i], fd);
		i++;
	}
	close(fd);
	return (FUNCT_SUCCESS);
}
