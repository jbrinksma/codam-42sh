/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_check_for_special.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 17:54:17 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/06 13:41:27 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tools_check_for_special(char *str)
{
	while (*str != '\0')
	{
		if (tools_is_special(*str) == true)
			return (true);
		str++;
	}
	return (false);
}
