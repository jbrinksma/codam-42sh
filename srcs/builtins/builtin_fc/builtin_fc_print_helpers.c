/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fc_print_helpers.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/11 13:03:14 by omulder        #+#    #+#                */
/*   Updated: 2019/10/15 15:51:05 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	add_tabs(char *str, char *new)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		new[j] = str[i];
		if (str[i] == '\n' && str[i + 1] != '\0')
		{
			j++;
			new[j] = '\t';
		}
		i++;
		j++;
	}
	return (true);
}

static int	add_tabs_after_newlines(char *str, char **new)
{
	int		i;
	int		tab_count;

	i = 0;
	tab_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] != '\0')
			tab_count++;
		i++;
	}
	if (tab_count == 0)
	{
		*new = str;
		return (false);
	}
	*new = ft_strnew(i + tab_count);
	if (*new == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	return (add_tabs(str, *new));
}

int			fc_list_print_line(t_historyitem *item, t_fcdata *fc)
{
	int		ret;
	char	*tmp;

	if (fc->options & FC_OPT_L)
	{
		ret = add_tabs_after_newlines(item->str, &tmp);
		if (ret == FUNCT_ERROR)
			return (FUNCT_FAILURE);
		if (fc->options & FC_OPT_N)
			ft_printf("\t%s\n", tmp);
		else
			ft_printf("%d\t%s\n", item->number, tmp);
		if (ret == true)
			ft_strdel(&tmp);
	}
	else
		ft_dprintf(fc->fd, "%s\n", item->str);
	return (FUNCT_SUCCESS);
}

void		fc_print_regular(t_historyitem *start, int len, t_fcdata *fc)
{
	t_historyitem	*probe;
	int				i;

	probe = start;
	i = 0;
	while (probe != NULL && i < len)
	{
		if (fc_list_print_line(probe, fc) == FUNCT_FAILURE)
			return ;
		probe = probe->next;
		i++;
	}
}

void		fc_print_reverse(t_historyitem *start, int len, t_fcdata *fc)
{
	t_historyitem	*probe;
	int				i;

	probe = start;
	i = 0;
	while (probe != NULL && i < len)
	{
		if (fc_list_print_line(probe, fc) == FUNCT_FAILURE)
			return ;
		probe = probe->prev;
		i++;
	}
}
