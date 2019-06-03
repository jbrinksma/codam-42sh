/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_line_to_array.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 18:55:25 by mavan-he       #+#    #+#                */
/*   Updated: 2019/06/03 16:59:17 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "vsh_history.h"
#include "libft.h"

int		history_line_to_array(char *line)
{
	int i;

	if (history_i < 500)
	{
		history[history_i] = ft_strdup(line);
		if (history[history_i] == NULL)
			return (FUNCT_ERROR);
	}
	else
	{
		ft_strdel(&history[0]);
		i = 0;
		while (i < 500 - 1)
		{
			history[i] = history[i + 1];
			i++;
		}
		history[500 - 1] = ft_strdup(line);
		if (history[500 - 1] == NULL)
			return (FUNCT_ERROR);
	}
	history_i++;
	history_tmp = history_i;
	return (FUNCT_SUCCESS);
}
