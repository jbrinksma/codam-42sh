/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_is_identifier_char.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/13 19:50:31 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/06 13:49:41 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tools_is_identifier_char(char c)
{
	return (ft_isalnum(c) == true || c == '_' || c == '-');
}
