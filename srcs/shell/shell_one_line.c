/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_one_line.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/15 21:53:03 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/15 14:48:28 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	shell_one_line takes a line through history_expansion,
**	lexer, alias_expansion, parser and executor
*/

int		shell_one_line(t_vshdata *data, char *line)
{
	t_tokenlst	*token_lst;
	t_ast		*ast;
	int			ret;

	token_lst = NULL;
	ast = NULL;
	ret = FUNCT_SUCCESS;
	data->line->line = ft_strdup(line);
	if (data->line->line == NULL || history_expansion(data) != FUNCT_SUCCESS ||
		(data->fc_flags & ~FC_SET_HIST &&
		history_add_item(data->history, data->line->line)
		== FUNCT_ERROR) || lexer(&data->line->line, &token_lst)
		!= FUNCT_SUCCESS || alias_expansion(data, &token_lst, NULL)
		!= FUNCT_SUCCESS)
		ret = FUNCT_ERROR;
	else if (token_lst->next->type == NEWLINE || token_lst->next->type == END)
		ret = FUNCT_SUCCESS;
	else if (parser_start(&token_lst, &ast) != FUNCT_SUCCESS ||
		exec_complete_command(ast, data) == FUNCT_ERROR)
		ret = FUNCT_ERROR;
	if (ret == FUNCT_ERROR && g_state->exit_code == EXIT_SUCCESS)
		g_state->exit_code = EXIT_FAILURE;
	shell_clear_input_data(&data->line->line, &ast, &token_lst);
	return (ret);
}
