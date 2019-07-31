/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_handle_escaped_newlines.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/31 14:18:35 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/31 15:26:31 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static bool	remove_last_escaped_newline(char *line)
{
	int i;

	i = ft_strlen(line);
	if (i == 0)
		return (false);
	i--;
	if (line[i] == '\n' && tools_is_char_escaped(line, i) == true)
	{
		line[i] = '\0';
		line[i - 1] = '\0';
		return (true);
	}
	return (false);
}

int			shell_handle_escaped_newlines(t_vshdata *vshdata, char **line,
			int *status)
{
	int		ret;
	char	*extra_line;

	ret = remove_last_escaped_newline(*line);
	if (ret == false)
		return (FUNCT_FAILURE);
	while (ret != false)
	{
		ft_putstr("\nlinecont> ");
		input_read(vshdata, &extra_line, status);
		*line = ft_strjoinfree_all(*line, extra_line);
		ret = remove_last_escaped_newline(*line);
	}
	return (FUNCT_SUCCESS);
}
