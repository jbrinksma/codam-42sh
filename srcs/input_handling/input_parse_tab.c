/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_tab.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/15 13:57:43 by omulder        #+#    #+#                */
/*   Updated: 2019/10/05 17:23:38 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	A tab will trigger autocomplete functionality.
*/

void	input_parse_tab(t_vshdata *data)
{
	auto_start(data);
}
