/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_add_chunk.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 10:25:30 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/06 10:25:40 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			input_add_chunk(t_vshdata *data, char *chunk, int chunk_len)
{
	char	*tmp;

	if (data->line->buffer == NULL)
	{
		data->line->buffer = ft_strdup(chunk);
		if (data->line->buffer == NULL)
			return (FUNCT_ERROR);
		return (FUNCT_SUCCESS);
	}
	else
	{
		tmp = ft_strnew(ft_strlen(data->line->buffer) + chunk_len);
		if (tmp == NULL)
			return (FUNCT_ERROR);
		ft_strcpy(tmp, data->line->buffer);
		ft_strcat(tmp, chunk);
		ft_strdel(&data->line->buffer);
		data->line->buffer = tmp;
	}
	return (FUNCT_SUCCESS);
}
