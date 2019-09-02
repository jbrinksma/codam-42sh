/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_y.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/23 13:05:41 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/29 14:32:43 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vsh.h>

static void	str_insert_str(t_vshdata *data, char *dst,
	char *src, unsigned src_len)
{
	ft_strncpy(&dst[data->line->index + src_len],
		&dst[data->line->index], data->line->len_cur - data->line->index);
	ft_strncpy(&dst[data->line->index], src, src_len);
}

static int	line_insert_copy(t_vshdata *data,
	unsigned copy_len)
{
	char		*tmp;

	if (data->line->len_cur + copy_len < data->line->len_max)
		str_insert_str(data, data->line->line, data->line->line_copy, copy_len);
	else
	{
		data->line->len_max += copy_len;
		tmp = ft_strnew(data->line->len_max);
		if (tmp == NULL)
			return (FUNCT_ERROR);
		ft_strcpy(tmp, data->line->line);
		ft_strdel(&data->line->line);
		str_insert_str(data, tmp, data->line->line_copy, copy_len);
		data->line->line = tmp;
	}
	data->line->len_cur += copy_len;
	return (FUNCT_SUCCESS);
}

void		input_parse_ctrl_y(t_vshdata *data)
{
	unsigned	copy_len;
	unsigned	old_index;

	if (data->line->line_copy != NULL)
	{
		old_index = data->line->index;
		copy_len = ft_strlen(data->line->line_copy);
		if (line_insert_copy(data, copy_len) == FUNCT_SUCCESS)
		{
			input_print_str(data, &data->line->line[data->line->index]);
			data->line->index = data->line->len_cur;
			curs_move_n_left(data, data->line->index - old_index - copy_len);
		}
	}
}
