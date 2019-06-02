/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_next_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/19 11:29:53 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/30 16:06:22 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static int		set_line(t_list *current, char **line)
{
	char *tmp;

	tmp = ft_strchr(current->content, '\n');
	if (!tmp)
	{
		*line = ft_strdup(current->content);
		free(current->content);
		current->content = ft_strdup("");
		if (!*line || !current->content)
			return (-1);
		return (1);
	}
	else
	{
		*tmp = 0;
		*line = ft_strdup(current->content);
		tmp = ft_strdup(tmp + 1);
		if (!tmp || !*line)
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
	if (!new)
		return (-1);
	new->content_size = fd;
	ft_lstadd(alist, new);
	*current = new;
	return (0);
}

static int		read_buff(t_list *current, const int fd)
{
	ssize_t ret;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;

	while (!ft_strchr(current->content, '\n'))
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
		if (!current->content)
			return (-1);
	}
	return (1);
}

int				ft_get_next_line(const int fd, char **line)
{
	static t_list	*file_list;
	t_list			*current;
	ssize_t			ret;

	if (fd < 0 || !line || get_lst(&file_list, fd, &current))
		return (-1);
	ret = read_buff(current, fd);
	if (ret == -1)
		return (-1);
	if (ret == 0 && *(char*)(current->content) == '\0')
		return (0);
	ret = set_line(current, line);
	return (ret);
}
