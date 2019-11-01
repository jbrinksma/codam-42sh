/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_close_quote_and_esc.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 20:00:00 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/31 20:00:07 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			shell_close_quote_and_esc(t_vshdata *data)
{
	int		ret;
	bool	ctrl_d;

	ret = FUNCT_SUCCESS;
	ctrl_d = false;
	while (ret == FUNCT_SUCCESS)
	{
		ret = shell_close_unclosed_quotes(data);
		if (ret == FUNCT_ERROR || ret == NEW_PROMPT)
			return (ret);
		else if (ret == IR_EOF)
			ctrl_d = true;
		ret = shell_handle_escaped_newlines(data);
		if (ret == FUNCT_ERROR || ret == NEW_PROMPT)
			return (ret);
		else if (ret == IR_EOF)
			ctrl_d = true;
	}
	if (ctrl_d == true)
		return (IR_EOF);
	return (FUNCT_SUCCESS);
}
