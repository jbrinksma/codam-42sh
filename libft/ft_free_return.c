/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_return.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/01 14:58:31 by tde-jong       #+#    #+#                */
/*   Updated: 2019/08/01 14:58:57 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_return(void *tofree, int ret)
{
	free(tofree);
	return (ret);
}
