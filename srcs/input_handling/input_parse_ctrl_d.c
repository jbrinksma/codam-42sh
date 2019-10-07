/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_d.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:46:55 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/06 10:10:27 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	CTRL+D can behave in one of three ways:
**	1.	If the line is empty and the current prompt is not the regular one
**		(perhaps `quote>`):
**			Return `IR_EOF` to indicate an EOT character was given.
**	2.	If the line is empty and the current prompt is the regular one:
**			Call builtin_exit.
**	3.	If the line is not empty.
**			Delete the character that the cursor is on at that moment.
*/

int		input_parse_ctrl_d(t_vshdata *data)
{
	if (data->input->c == INPUT_CTRL_D)
	{
		if (data->line->len_cur == 0
			&& data->prompt->cur_prompt_type != REGULAR_PROMPT)
		{
			ft_putchar('\n');
			return (IR_EOF);
		}
		else if (data->line->len_cur == 0)
			builtin_exit(NULL, data);
		else
			input_handle_delete(data);
	}
	else
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
