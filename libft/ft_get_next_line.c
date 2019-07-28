/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_next_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/19 11:29:53 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/18 16:30:52 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static int		set_line(t_list *current, char **line, char delim)
{
	char *tmp;

	tmp = ft_strchr(current->content, delim);
	if (tmp == NULL)
	{
		*line = ft_strdup(current->content);
		free(current->content);
		current->content = ft_strdup("");
		if (*line == NULL || current->content == NULL)
			return (-1);
		return (1);
	}
	else
	{
		*tmp = 0;
		*line = ft_strdup(current->content);
		tmp = ft_strdup(tmp + 1);
		if (tmp == NULL || *line == NULL)
			return (-1);
		free(current->content);
		current->content = tmp;
	}
	return (1);
}

static int		get_lst(t_list **alist, const int fd, t_list **current)
{
	t_list *new;

	new = *alist;
	while (new)
	{
		if ((int)new->content_size == fd)
		{
			*current = new;
			return (0);
		}
		new = new->next;
	}
	new = ft_lstnew("", 1);
	if (new == NULL)
		return (-1);
	new->content_size = fd;
	ft_lstadd(alist, new);
	*current = new;
	return (0);
}

static int		read_buff(t_list *current, const int fd, char delim)
{
	ssize_t ret;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;

	while (ft_strchr(current->content, delim) == NULL)
	{
		ret = read(fd, &buff, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			return (0);
		buff[ret] = 0;
		tmp = current->content;
		current->content = ft_strjoin(current->content, buff);
		free(tmp);
		if (current->content == NULL)
			return (-1);
	}
	return (1);
}

int				ft_get_next_line_delim(const int fd, char **line, char delim)
{
	static t_list	*file_list;
	t_list			*current;
	ssize_t			ret;

	if (fd < 0 || line == NULL || get_lst(&file_list, fd, &current))
		return (-1);
	ret = read_buff(current, fd, delim);
	if (ret == -1)
		return (-1);
	if (ret == 0 && *(char*)(current->content) == '\0')
		return (0);
	ret = set_line(current, line, delim);
	return (ret);
}

int				ft_get_next_line(const int fd, char **line)
{
	return (ft_get_next_line_delim(fd, line, '\n'));
}
