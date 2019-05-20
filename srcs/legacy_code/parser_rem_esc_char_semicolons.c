/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_rem_esc_char_semicolons.c                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 20:24:50 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/05 12:17:54 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Remove any escape chars that are escaping a semicolon char
*/

void	parser_rem_esc_char_semicolons(t_list *cmdstr_lst)
{
	int		i;
	char	*cmd;
	int		len;
	char	quote;

	while (cmdstr_lst != NULL)
	{
		if (cmdstr_lst->content != NULL)
		{
			i = 0;
			cmd = cmdstr_lst->content;
			quote = '\0';
			while (cmd[i] != '\0')
			{
				update_quote_status(cmd, i, &quote);
				if (cmd[i] == ';' && is_char_escaped(cmd, i) == true && !quote)
				{
					len = ft_strlen(&cmd[i]);
					ft_memmove(&cmd[i - 1], &cmd[i], len + 1);
				}
				i++;
			}
		}
		cmdstr_lst = cmdstr_lst->next;
	}
}
