/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_reset_cursor_pos.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/05 16:46:40 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/07 12:19:43 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	This function will move the cursor to the bottom left of a new line,
**	and will make sure to mark its old location with a zsh-like `%` character.
**	This character is printed so that you are aware that the newline was not
**	natural. This is used, for example, before a new prompt is printed, so that
**	it always looks neat.
*/

void		input_reset_cursor_pos(void)
{
	size_t		i;
	size_t		len;
	int			output;
	char		answer[TC_MAXRESPONSESIZE];

	len = 0;
	write(STDIN_FILENO, TC_GETCURSORPOS, 4);
	while (len < TC_MAXRESPONSESIZE - 1 && read(1, answer + len, 1) == 1)
	{
		if (answer[len] == 'R')
			break ;
		len++;
	}
	answer[len] = '\0';
	i = 1;
	while (i < len && answer[i] != ';')
		i++;
	if (answer[i] != '\0')
	{
		i++;
		output = ft_atoi(&answer[i]);
		if (output > 1)
			ft_putstr(WHITE_BG_BLACK "%" RESET "\n");
	}
	g_data->curs->coords.x = 1;
}
