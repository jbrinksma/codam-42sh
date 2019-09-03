/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_big_lst.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 20:07:40 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/16 19:29:53 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		auto_big_lst(t_list **matchlst, int lst_len)
{
	char	c;
	int		ret;

	ft_printf("\nDisplay all %d possibilities? (y or n)", lst_len);
	c = 0;
	while (c != 'y' && c != 'n')
	{
		ret = read(STDIN_FILENO, &c, 1);
		if (ret == -1)
		{
			ft_eprintf(E_READ_STR);
			return (FUNCT_ERROR);
		}
		else if (ret == 1)
			ft_putchar('\a');
	}
	ft_putchar('\n');
	if (c == 'y')
		auto_lst_print(matchlst, lst_len);
	else if (c == 'n')
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
