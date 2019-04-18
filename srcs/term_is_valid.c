/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_is_valid.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:16:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/18 18:17:06 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		term_is_valid(void)
{
	char	*term_type;
	int		ret;

	term_type = getenv("TERM");
	if (!term_type)
	{
		ft_eprintf("Term env not set.\n");
		return (FUNCT_FAILURE);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		ft_eprintf("Terminfo database could not be found.\n");
	if (ret == 0)
		ft_eprintf("No such TERM entry in the database\n");
	if (ret == -1 || ret == 0)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
