/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init_line.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/15 20:47:40 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/17 13:11:03 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static bool	is_binary_file(char *line, int ret)
{
	int i;

	i = 0;
	while (i < ret)
	{
		if (line[i] == '\n')
			return (false);
		if (line[i] == '\0')
			return (true);
		i++;
	}
	return (false);
}

int			shell_init_line(t_vshdata *data, char *filepath)
{
	int			fd;
	int			ret;
	struct stat file_info;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (err_ret_exit(E_FAIL_OPEN, EXIT_FAILURE));
	if (fstat(fd, &file_info) == -1)
		return (err_ret_exit(E_STAT_STR, EXIT_FAILURE));
	data->line->line = ft_strnew((file_info.st_size));
	if (data->line->line == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	ret = read(fd, data->line->line, file_info.st_size);
	if (ret == -1)
		return (err_ret_exit(E_READ_FILE_STR, EXIT_FAILURE));
	close(fd);
	if (ret > 80)
		ret = 80;
	if (is_binary_file(data->line->line, ret) == true)
		return (err_ret_exit(E_BINARY_FILE, EXIT_FAILURE));
	data->line->line = ft_strjoinfree_s1(data->line->line, "\n");
	if (data->line->line == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	return (FUNCT_SUCCESS);
}
