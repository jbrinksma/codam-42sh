/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tool_is_cmd_seperator.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 17:46:55 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/23 17:48:43 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tools_is_cmd_seperator(t_tokens type)
{
	return (type == PIPE || type == AND_IF || type == OR_IF || type == BG ||
		type == SEMICOL || type == NEWLINE);
}
