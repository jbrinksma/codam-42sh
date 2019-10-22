/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_expansion.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/10 12:37:29 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/22 11:46:36 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	!      		Start a history substitution, except when followed by:
**				a space, tab, the end of the line, '=' or '('.
**	!n     		Refer to command line on history n.
**	!-n    		Refer to the command n lines back.
**	!!     		Refer to the previous command. This is a synonym for '!-1'.
**	!string		Refer to the most recent command starting with string.
*/

#include "vsh.h"

int		history_expand(t_datahistory *history, char **line, size_t *i)
{
	char *history_line;

	history_line = history_get_line(history, *line, *i);
	if (history_line == NULL)
		return (FUNCT_ERROR);
	if (history_insert_into_line(line, history_line, *i) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	*i = *i + ft_strlen(history_line) - 1;
	return (FUNCT_SUCCESS);
}

int		history_expansion(t_vshdata *data)
{
	size_t	i;
	int		state;

	state = 0;
	i = 0;
	while (data->line->line[i] != '\0')
	{
		if (data->line->line[i] == '\\')
			i++;
		else if (data->line->line[i] == '\'')
			state ^= T_STATE_SQUOTE;
		else if (data->line->line[i] == '!' && (state & T_STATE_SQUOTE) == false
			&& ft_strchr("\n\t =(", data->line->line[i + 1]) == NULL)
		{
			if (history_expand(data->history, &data->line->line, &i)
				!= FUNCT_SUCCESS)
				return (FUNCT_ERROR);
			state |= HIST_EXPANDED;
		}
		i++;
	}
	if (state & HIST_EXPANDED)
		ft_printf("%s", data->line->line);
	return (FUNCT_SUCCESS);
}
