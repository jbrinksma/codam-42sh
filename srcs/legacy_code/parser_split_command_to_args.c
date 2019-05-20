/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_split_command_to_args.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 20:48:21 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/05 12:54:16 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	NOTE: This code is nowhere near from perfect and any help and/or suggestions
**	are appreciated.
*/

#include "vsh.h"

/*
**	Returns the amount of characters before reaching a '\0' char or a
**	uninhibited ';' char.
*/

int		parser_strlen_arg(char *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	update_quote_status(cmd, i, &quote);
	while (cmd[i] != '\0' && is_uninhibited_blank(cmd, i, quote) != true)
	{
		i++;
		update_quote_status(cmd, i, &quote);
	}
	return (i);
}

/*
**	Splits one command into it's arguments (which are delimited by uninhibited
**	'\t' and ' ' chars) as strings.
*/

t_list	*parser_split_command_to_args(char *cmd)
{
	t_list		*arg_lst;
	char		*arg;
	int			i;
	int			len;

	arg_lst = NULL;
	i = 0;
	while (cmd[i] != '\0')
	{
		while (ft_isblank(cmd[i]) == true)
			i++;
		len = parser_strlen_arg(&cmd[i]);
		if (len > 0)
		{
			arg = ft_strndup(&cmd[i], len);
			add_str_to_lst(arg, &arg_lst);
			ft_strdel(&arg);
			i += len;
		}
		else
			i++;
	}
	return (arg_lst);
}
