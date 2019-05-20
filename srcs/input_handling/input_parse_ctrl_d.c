/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_d.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:46:55 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/20 11:41:47 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int				input_parse_ctrl_d(char c, unsigned *index, char **line)
{
	unsigned	i;
	unsigned	len;

	if (c == '\4')
	{
		len = ft_strlen(*line);
		if (len == 0)
			exit(0);
		if (*index < len)
		{
			i = 0;
			input_clear_char_at(line, *index);
			ft_printf("%s ", *line + *index);
			ft_printf("\e[%dD", ft_strlen(*line + *index) + 1);
		}
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
