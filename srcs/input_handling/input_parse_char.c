/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_char.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:33:54 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/20 12:49:02 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int		add_char_at(char **line, int index, char c)
{
	int			i;
	char		*tmp;

	i = ft_strlen(*line);
	tmp = ft_strnew(i + 1);
	if (tmp == NULL)
		return (FUNCT_FAILURE);
	ft_strncpy(tmp, *line, i);
	i--;
	while (i >= index)
	{
		tmp[i + 1] = (*line)[i];
		i--;
	}
	tmp[index] = c;
	ft_strdel(line);
	*line = tmp;
	return (FUNCT_SUCCESS);
}

int				input_parse_char(char c, unsigned *index, char **line)
{
	unsigned len;
	
	if (ft_isprint(c))
	{
		if (add_char_at(line, *index, c) == FUNCT_FAILURE)
			return (FUNCT_FAILURE);
		len = ft_strlen(*line + *index);
		ft_printf("%s", *line + *index);
		if (len - 1 > 0)
			ft_printf("\e[%dD", len - 1);
		*index += 1;
	}
	return (FUNCT_SUCCESS);
}
