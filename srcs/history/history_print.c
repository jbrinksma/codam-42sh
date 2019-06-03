/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_print.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 20:47:41 by mavan-he       #+#    #+#                */
/*   Updated: 2019/06/03 15:29:07 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "vsh_history.h"
#include "libft.h"

void	history_print(void)
{
	int i;
	int tmp;

	i = 0;
	tmp = 1;
	if (history_i >= 500)
		tmp = history_i - (500 - 1);
	while (i < 500 && history[i] != NULL)
	{
		ft_printf("%5d  %s\n", tmp, history[i]);
		i++;
		tmp++;
	}
}
