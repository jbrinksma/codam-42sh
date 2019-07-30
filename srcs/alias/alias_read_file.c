/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias_read_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/29 13:27:43 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/30 10:54:47 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>
#include <fcntl.h>

static int	get_line_in_alias(int fd, t_vshdata *vshdata)
{
	int			ret;
	char		*line;
	char		*args[3];

	line = NULL;
	ret = ft_get_next_line(fd, &line);
	if (ret == -1)
		return (FUNCT_ERROR);
	if (ret == 0)
		return (FUNCT_FAILURE);
	args[0] = "alias";
	args[1] = line;
	args[2] = NULL;
	builtin_alias(args, &vshdata->aliaslst);
	ft_strdel(&line);
	if (g_state->exit_code == EXIT_FAILURE)
		return (FUNCT_ERROR);
	return (ret);
}

int			alias_read_file(t_vshdata *vshdata)
{
	int		fd;
	int		ret;

	if (access(vshdata->alias_file, R_OK) != 0)
		return (FUNCT_FAILURE);
	fd = open(vshdata->alias_file, O_RDONLY);
	if (fd == -1)
		return (FUNCT_ERROR);
	ret = 1;
	while (ret > 0)
	{
		ret = get_line_in_alias(fd, vshdata);
		if (ret == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	close(fd);
	return (FUNCT_SUCCESS);
}
