/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_dless_input.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/02 13:23:16 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/30 13:56:37 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

int			shell_dless_read_till_stop(char **heredoc, char *heredoc_delim,
			t_vshdata *data)
{
	char	*line_tmp;

	line_tmp = data->line->line;
	data->line->line = NULL;
	while (true)
	{
		ft_putstr(PROMPT_SEPERATOR);
		if (input_read(data) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		ft_putstr("\n");
		if (ft_strequ(data->line->line, heredoc_delim) == true)
			break ;
		if (*heredoc == NULL)
			*heredoc = ft_strdup(data->line->line);
		else
			*heredoc = ft_strjoinfree_s1(*heredoc, data->line->line);
		ft_strdel(&data->line->line);
		if (*heredoc == NULL)
			return (err_ret(E_ALLOC_STR));
	}
	ft_strdel(&data->line->line);
	data->line->line = line_tmp;
	return (FUNCT_SUCCESS);
}

int			shell_dless_set_tk_val(t_tokenlst *probe, char **heredoc,
			char *heredoc_delim, t_vshdata *data)
{
	int	ret;

	ft_strdel(&(probe->value));
	ret = shell_dless_read_till_stop(heredoc, heredoc_delim, data);
	if (ret == FUNCT_SUCCESS)
	{
		if (*heredoc != NULL)
			probe->value = ft_strdup(*heredoc);
		else
			probe->value = ft_strnew(0);
	}
	if (probe->value == NULL)
	{
		ft_strdel(heredoc);
		ft_strdel(&heredoc_delim);
		return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}

static bool	is_valid_heredoc_delim(t_tokenlst *token)
{
	g_state->exit_code = EXIT_FAILURE;
	if (token->type != WORD && token->type != ASSIGN)
	{
		ft_eprintf(E_SYNTAX_P,
			parser_return_token_str(token->type));
		return (false);
	}
	if (token->value == NULL)
	{
		ft_eprintf(E_P_NOT_VAL_HERE,
			token->value);
		return (false);
	}
	g_state->exit_code = EXIT_SUCCESS;
	return (true);
}

static int	return_alloc_error(int ret)
{
	ft_eprintf(E_N_ALLOC_STR, "heredoc");
	return (ret);
}

int			shell_dless_input(t_vshdata *data, t_tokenlst **token_lst)
{
	char		*heredoc;
	t_tokenlst	*probe;
	char		*heredoc_delim;

	probe = *token_lst;
	heredoc = NULL;
	while (probe != NULL)
	{
		if (probe->type == DLESS)
		{
			probe = probe->next;
			if (is_valid_heredoc_delim(probe) == false)
				return (FUNCT_ERROR);
			heredoc_delim = ft_strjoin(probe->value, "\n");
			if (heredoc_delim == NULL || shell_dless_set_tk_val(probe, &heredoc,
			heredoc_delim, data) == FUNCT_ERROR)
				return (return_alloc_error(FUNCT_ERROR));
			ft_strdel(&heredoc);
			ft_strdel(&heredoc_delim);
		}
		probe = probe->next;
	}
	return (FUNCT_SUCCESS);
}
