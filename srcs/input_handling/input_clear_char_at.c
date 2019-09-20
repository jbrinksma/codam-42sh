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

static void	remove_tabulations(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

int			input_add_chunk(t_vshdata *data, char *chunk, int chunk_len,
	int index)
{
	char *tmp;

	while (data->line->len_cur + chunk_len > data->line->len_max)
		data->line->len_max *= 2;
	tmp = ft_strnew(data->line->len_max);
	if (tmp == NULL)
		return (FUNCT_ERROR);
	remove_tabulations(chunk);
	ft_strncpy(tmp, data->line->line, data->line->index + index);
	ft_strcat(tmp, chunk);
	ft_strcat(tmp, &data->line->line[data->line->index + index]);
	ft_strdel(&data->line->line);
	data->line->line = tmp;
	return (FUNCT_SUCCESS);
}

void		input_clear_char_at(char **line, unsigned index)
{
	unsigned i;

	i = index;
	while ((*line)[i])
	{
		(*line)[i] = (*line)[i + 1];
		i++;
	}
}
