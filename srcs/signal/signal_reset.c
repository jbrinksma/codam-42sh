/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_reset.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/21 13:44:58 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/29 11:47:27 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

void	signal_reset(void)
{
	int i;

	i = 1;
	while (i < 32)
	{
		signal(i, SIG_DFL);
		i++;
	}
}
