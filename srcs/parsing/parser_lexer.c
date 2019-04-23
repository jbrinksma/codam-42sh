/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_lexer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:57:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 14:24:40 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	IMPORTANT: add check for more than one ';' command seperator.
**	It's not allowed.
*/

#include "vsh.h"

int			parser_lexer(char *line, char ***commands)
{
	*commands = parser_split_commands(line);
	if (*commands == NULL)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
