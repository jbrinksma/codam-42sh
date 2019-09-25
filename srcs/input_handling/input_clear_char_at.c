/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_clear_char_at.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/30 10:30:47 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/30 10:38:06 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			input_read_from_buffer(t_vshdata *data)
{
	if (data->line->buffer != NULL)
	{
		if (data->line->buffer[data->line->buffer_i] != '\0')
		{
			data->input->c = data->line->buffer[data->line->buffer_i];
			data->line->buffer_i++;
		}
		else
		{
			ft_strdel(&data->line->buffer);
			data->line->buffer = NULL;
			data->line->buffer_i = 0;
			return (FUNCT_FAILURE);
		}
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}

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

void		input_clear_char_at(char **line, unsigned index)
{
	while ((*line)[index])
	{
		(*line)[index] = (*line)[index + 1];
		index++;
	}
}
