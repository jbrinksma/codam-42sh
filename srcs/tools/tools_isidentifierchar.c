/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_isidentifierchar.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/13 19:50:31 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/31 12:26:29 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tools_isidentifierchar(char c)
{
	return (ft_isalnum(c) == true || c == '_');
}
