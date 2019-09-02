/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_isprintnotblank.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/08 15:25:53 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/08 15:25:59 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			tools_isprintnotblank(int i)
{
	if (ft_isprint(i) == true && ft_isblank(i) == false)
		return (true);
	return (false);
}
