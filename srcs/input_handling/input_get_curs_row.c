/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_get_curs_row.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/05 16:51:25 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/05 16:51:31 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			input_get_curs_row(void)
{
	size_t		i;
	size_t		len;
	int			row;
	char		answer[TC_MAXRESPONSESIZE];

	len = 0;
	write(STDIN_FILENO, TC_GETCURSORPOS, 4);
	while (len < TC_MAXRESPONSESIZE - 1 && read(1, answer + len, 1) == 1)
	{
		if (answer[len] == 'R')
			break ;
		len++;
	}
	i = 1;
	answer[len] = '\0';
	while (answer[i - 1] != '[' && answer[i] != '\0')
		i++;
	if (ft_isdigit(answer[i]) == false)
		return (-1);
	row = ft_atoi(&answer[i]);
	return (row);
}
