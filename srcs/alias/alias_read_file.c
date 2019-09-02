/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias_read_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/29 13:27:43 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/26 18:40:47 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>
#include <fcntl.h>

static int	get_line_in_alias(int fd, t_vshdata *data)
{
	int			ret;
	char		*line;
	char		*args[3];

	line = NULL;
	ret = ft_get_next_line(fd, &line);
	if (ret == -1)
		return (err_ret(E_ALIAS_READ_STR));
	if (ret == 0)
		return (FUNCT_FAILURE);
	args[0] = "alias";
	args[1] = line;
	args[2] = NULL;
	builtin_alias(args, &data->alias->aliaslst);
	ft_strdel(&line);
	if (g_state->exit_code == EXIT_FAILURE)
		return (FUNCT_ERROR);
	return (ret);
}

int			alias_read_file(t_vshdata *data)
{
	int		fd;
	int		ret;

	if (access(data->alias->alias_file, F_OK) != 0)
		return (FUNCT_FAILURE);
	if (access(data->alias->alias_file, R_OK) != 0)
	{
		ft_eprintf(E_N_PER_DEN_P, "alias", data->alias->alias_file);
		return (FUNCT_FAILURE);
	}
	fd = open(data->alias->alias_file, O_RDONLY);
	if (fd == -1)
		return (err_ret(E_ALIAS_OPEN_STR));
	ret = 1;
	while (ret > 0)
	{
		ret = get_line_in_alias(fd, data);
		if (ret == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	close(fd);
	return (FUNCT_SUCCESS);
}
