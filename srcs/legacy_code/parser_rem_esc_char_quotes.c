/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_rem_esc_char_quotes.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 20:24:50 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/02 20:38:58 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Remove any escape chars that are escaping a quote char
*/

void	parser_rem_esc_char_quotes(t_list *cmdstr_lst)
{
	int		i;
	char	*cmd;
	int		len;

	while (cmdstr_lst != NULL)
	{
		if (cmdstr_lst->content != NULL)
		{
			i = 0;
			cmd = cmdstr_lst->content;
			while (cmd[i] != '\0')
			{
				if (cmd[i] == '"' || cmd[i] == '\'')
				{
					if (is_char_escaped(cmd, i) == true)
					{
						len = ft_strlen(&cmd[i]);
						ft_memmove(&cmd[i - 1], &cmd[i], len + 1);
					}
				}
				i++;
			}
		}
		cmdstr_lst = cmdstr_lst->next;
	}
}
