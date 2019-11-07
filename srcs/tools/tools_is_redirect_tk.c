/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_is_redirect_tk.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/27 17:17:11 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/06 13:41:55 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tools_is_redirect_tk(t_tokens type)
{
	return (type == SLESS || type == SGREAT || type == DLESS ||
			type == DGREAT || type == LESSAND || type == GREATAND);
}
