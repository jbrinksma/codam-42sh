/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/26 12:11:35 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/16 15:46:08 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static char	*return_single_tk_str(t_tokens type)
{
	if (type == AND_IF)
		return ("&&");
	else if (type == OR_IF)
		return ("||");
	else if (type == DLESS)
		return ("<<");
	else if (type == DGREAT)
		return (">>");
	else if (type == SLESS)
		return ("<");
	else if (type == SGREAT)
		return (">");
	else if (type == LESSAND)
		return ("<&");
	else if (type == GREATAND)
		return (">&");
	else if (type == BG)
		return ("&");
	else if (type == PIPE)
		return ("|");
	else if (type == SEMICOL)
		return (";");
	else
		return ("ERROR");
}

char		*parser_return_token_str(t_tokens type)
{
	if (type == START)
		return ("START");
	else if (type == ASSIGN)
		return ("ASSIGN");
	else if (type == WORD)
		return ("WORD");
	else if (type == IO_NUMBER)
		return ("IO_NUM");
	else if (type == NEWLINE)
		return ("NEWLINE");
	else if (type == END)
		return ("END");
	else
		return (return_single_tk_str(type));
}
