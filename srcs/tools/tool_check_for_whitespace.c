/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tool_check_for_whitespace.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 17:54:17 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/21 17:54:54 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tool_check_for_whitespace(char *str)
{
	while (*str != '\0')
	{
		if (ft_isspace(*str) == true)
			return (true);
		str++;
	}
	return (false);
}
