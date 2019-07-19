/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 20:08:54 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/01/14 16:08:07 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	if (ft_isdigit(c) != 0 || ft_isalpha(c) != 0)
		return (1);
	else
		return (0);
}
