/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   words_to_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/19 15:59:36 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/19 16:00:52 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		init_cmd(t_list *token_lst, char ***new)
{
	int count;

	count = 0;
	while (((t_token*)token_lst->content)->type == WORD)
	{
		count++;
		token_lst = token_lst->next;
	}
	*new = (char **)malloc(sizeof(char *) * (count + 1));
	if (*new == NULL)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int		words_to_cmds(t_list *token_lst)
{
	char	**cmd;
	t_list	*tmp;
	int		i;

	while (token_lst)
	{
		if (((t_token*)token_lst->content)->type == WORD)
		{
			if (init_cmd(token_lst, &cmd) == FUNCT_ERROR)
				return (FUNCT_ERROR);
			i = 0;
			tmp = token_lst;
			cmd[i] = ((t_token*)token_lst->content)->value.str;
			i++;
			token_lst = token_lst->next;
			while (((t_token*)token_lst->content)->type == WORD)
			{
				cmd[i] = ((t_token*)token_lst->content)->value.str;
				free(token_lst->content);
				free(token_lst);
				token_lst = token_lst->next;
				i++;
			}
			cmd[i] = NULL;
			((t_token*)tmp->content)->type = CMD;
			((t_token*)tmp->content)->value.array = cmd;
			tmp->next = token_lst;
		}
		else
			token_lst = token_lst->next;
	}
	return (FUNCT_SUCCESS);
}