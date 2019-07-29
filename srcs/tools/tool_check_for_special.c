/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tool_check_for_whitespace.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 17:54:17 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/29 11:35:38 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tool_check_for_special(char *str)
{
	while (*str != '\0')
	{
		if (tool_is_special(*str) == true)
			return (true);
		str++;
	}
	return (false);
}
