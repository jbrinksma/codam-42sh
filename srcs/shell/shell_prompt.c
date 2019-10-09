/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_prompt.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 20:16:38 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/08 22:09:06 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	shell_get_valid_prompt(t_vshdata *data, int prompt_type)
{
	if (prompt_type == QUOTE_PROMPT)
		data->prompt->prompt_name = "quote";
	else if (prompt_type == DQUOTE_PROMPT)
		data->prompt->prompt_name = "dquote";
	else if (prompt_type == LINECONT_PROMPT)
		data->prompt->prompt_name = "linecont";
	else if (prompt_type == DLESS_PROMPT)
		data->prompt->prompt_name = "";
	else
		data->prompt->prompt_name = PROMPT_NAME;
	data->prompt->prompt_seperator = PROMPT_SEPERATOR;
	if (data->prompt->prompt_addition != NULL && prompt_type == REGULAR_PROMPT)
		data->prompt->prompt_len = ft_strlen(data->prompt->prompt_name)
			+ ft_strlen(data->prompt->prompt_seperator)
			+ ft_strlen(data->prompt->prompt_addition) + 1;
	else
		data->prompt->prompt_len = ft_strlen(data->prompt->prompt_name)
		+ ft_strlen(data->prompt->prompt_seperator);
}

void	shell_display_prompt(t_vshdata *data, int prompt_type)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	data->prompt->prompt_addition = shell_getcurrentdir(cwd);
	shell_get_valid_prompt(data, prompt_type);
	data->prompt->cur_prompt_type = prompt_type;
	input_empty_buffer(data, 0);
	input_reset_cursor_pos();
	if (prompt_type == REGULAR_PROMPT)
		ft_printf(RED);
	input_print_str(data, data->prompt->prompt_name);
	if (data->prompt->prompt_addition != NULL && prompt_type == REGULAR_PROMPT)
	{
		ft_printf(BLU);
		input_print_str(data, data->prompt->prompt_addition);
		input_print_str(data, " ");
	}
	if (prompt_type == REGULAR_PROMPT && g_state->exit_code == EXIT_SUCCESS)
		ft_printf(YEL);
	else if (prompt_type == REGULAR_PROMPT)
		ft_printf(RED);
	input_print_str(data, data->prompt->prompt_seperator);
	ft_printf(RESET);
	ft_strdel(&cwd);
}
