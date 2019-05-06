/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_remove_quotes.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 20:07:16 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/02 20:40:54 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Removes any unescaped quotes from the cmdstr_lst
*/

void	parser_remove_quotes(t_list *cmdstr_lst)
{
	int		i;
	char	quote;
	char	*cmd;
	int		len;

	while (cmdstr_lst != NULL)
	{
		if (cmdstr_lst->content != NULL)
		{
			i = 0;
			quote = '\0';
			cmd = cmdstr_lst->content;
			while (cmd[i] != '\0')
			{
				if (update_quote_status(cmd, i, &quote) == true)
				{
					len = ft_strlen(&cmd[i + 1]);
					ft_memmove(&cmd[i], &cmd[i + 1], len + 1);
				}
				else
					i++;
			}
		}
		cmdstr_lst = cmdstr_lst->next;
	}
}
