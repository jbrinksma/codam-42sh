/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_print_str.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/23 11:54:27 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/30 16:56:16 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vsh.h>
#include <termios.h>
#include <term.h>

static int	get_curs_row_return(t_vshdata *data, char **buf, char *error_str,
	int ret)
{
	ft_strdel(buf);
	if (error_str != NULL)
		ft_eprintf(error_str);
	data->term->termios_p->c_cc[VMIN] = 0;
	data->term->termios_p->c_cc[VTIME] = 2;
	if (tcsetattr(STDIN_FILENO, TCSANOW, data->term->termios_p) == -1)
	{
		ft_eprintf(E_TERM_CNT_SET);
		return (FUNCT_ERROR);
	}
	return (ret);
}

static int	prepare_term_settings(t_vshdata *data)
{
	int		ret;

	data->term->termios_p->c_cc[VMIN] = 5;
	data->term->termios_p->c_cc[VTIME] = 0;
	ret = tcsetattr(STDIN_FILENO, TCSANOW, data->term->termios_p);
	if (ret == -1)
		return (get_curs_row_return(data, NULL, E_TERM_CNT_SET, FUNCT_ERROR));
	return (FUNCT_SUCCESS);
}

int			get_curs_row(t_vshdata *data)
{
	char	*buf;
	int		i;
	int		row;

	i = 0;
	if (prepare_term_settings(data) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	buf = ft_strnew(TC_MAXRESPONSESIZE);
	if (buf == NULL)
		return (get_curs_row_return(data, &buf, E_ALLOC_STR, FUNCT_ERROR));
	ft_putstr("\e[6n");
	if (read(STDIN_FILENO, buf, TC_MAXRESPONSESIZE) == -1)
		return (get_curs_row_return(data, &buf, NULL, FUNCT_ERROR));
	while (buf[i] != '[' && buf[i] != '\0')
		i++;
	if (buf[i] == '[')
		i++;
	#ifdef DEBUG
	ft_eprintf("curs: <%s>\n", &buf[1]);
	#endif
	if (ft_isdigit(buf[i]) == false)
		return (get_curs_row_return(data, &buf, NULL, FUNCT_ERROR));
	row = ft_atoi(&buf[i]);
	return (get_curs_row_return(data, &buf, NULL, row));
}

static void	scroll_down_terminal(t_vshdata *data)
{
	ft_printf("\e[%iD", data->curs->coords.x - 1);
	tputs(data->termcaps->tc_scroll_down_str, 1, &ft_tputchar);
	ft_printf("\e[%iC", data->curs->coords.x - 1);
}

void		input_print_str(t_vshdata *data, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		if (str[i] == '\n')
		{
			data->curs->coords.x = 1;
			data->curs->coords.y++;
			data->curs->cur_relative_y++;
		}
		i++;
		data->curs->coords.x++;
		if (data->curs->coords.x > data->curs->cur_ws_col)
		{
			if (data->curs->coords.y == data->curs->cur_ws_row)
				scroll_down_terminal(data);
			else
				data->curs->coords.y++;
			ft_printf("\e[B\e[%iD", data->curs->cur_ws_col);
			data->curs->coords.x = 1;
			data->curs->cur_relative_y++;
		}
	}
}
