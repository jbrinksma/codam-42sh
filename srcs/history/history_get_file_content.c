/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_get_file_content.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 13:49:22 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/17 17:08:49 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <fcntl.h>
#include "libft.h"
#include <unistd.h>

/*
** Get the content out of the history file
*/

static int		get_line_in_history(int fd, t_datahistory *history)
{
	int		ret;
	char	*line;

	line = NULL;
	ret = ft_get_next_line_delim(fd, &line, HIST_SEPARATE);
	if (ret == -1)
		return (err_ret(E_HIST_READ_STR));
	if (line != NULL && line[0] != '\0')
		history_add_item(history, line);
	ft_strdel(&line);
	return (ret);
}

static void		empty_gnl(int fd)
{
	int		ret;
	char	*line;

	line = NULL;
	ret = ft_get_next_line_delim(fd, &line, HIST_SEPARATE);
	while (ret != 0 && ret != -1)
	{
		ft_strdel(&line);
		ret = ft_get_next_line_delim(fd, &line, HIST_SEPARATE);
	}
}

char			*history_get_filename(void)
{
	char	*filename;
	char	*homedir;
	char	*fullpath;

	filename = env_getvalue("HISTFILE", g_data->envlst);
	if (filename == NULL)
		filename = HISTFILENAME;
	homedir = env_getvalue("HOME", g_data->envlst);
	if (homedir == NULL)
	{
		ft_eprintf(E_HOME_NOTSET_STR);
		return (NULL);
	}
	fullpath = ft_strjoinfree_s2(homedir, ft_strjoin("/", filename));
	if (fullpath == NULL)
	{
		ft_eprintf(E_N_ALLOC_STR, "history");
		return (NULL);
	}
	return (fullpath);
}

int				history_get_histsize(void)
{
	char	*size;
	int		histsize;

	size = env_getvalue("HISTSIZE", g_data->envlst);
	if (size == NULL)
		return (DEF_HISTSIZE);
	if (ft_aisint(size))
	{
		histsize = ft_atoi(size);
		return (histsize);
	}
	return (DEF_HISTSIZE);
}

int				history_get_file_content(t_datahistory *history)
{
	int		fd;
	int		ret;
	int		i;
	int		size;
	char	*histfile;

	histfile = history_get_filename();
	if (histfile == NULL)
		return (FUNCT_ERROR);
	fd = open(histfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (ft_free_return(histfile, err_ret(E_HIST_OPEN_STR)));
	ret = 1;
	size = history_get_histsize();
	i = 0;
	while (ret > 0 && i < size)
	{
		ret = get_line_in_history(fd, history);
		if (ret == FUNCT_ERROR)
			return (ft_free_return(histfile, FUNCT_ERROR));
		i++;
	}
	empty_gnl(fd);
	close(fd);
	return (ft_free_return(histfile, FUNCT_SUCCESS));
}
