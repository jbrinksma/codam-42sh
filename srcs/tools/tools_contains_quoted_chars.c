/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_contains_quoted_chars.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 15:48:57 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/23 15:49:26 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tools_contains_quoted_chars(char *str)
{
	if (str == NULL)
		return (false);
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'' || *str == '\\')
			return (true);
		str++;
	}
	return (false);
}
