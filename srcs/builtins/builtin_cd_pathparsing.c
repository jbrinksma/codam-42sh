/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd_pathparsing.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/02 14:51:29 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/19 18:14:40 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Wrapper function for builtin_cd_create_newpath.
**	If `argpath` starts with '/', it means that an absolute path will
**	be used instead of a relative path and there is no need to copy
**	currpath into newpath.
*/

char		*builtin_cd_create_newpath_wrap(char *currpath, char *argpath)
{
	char	*newpath;

	if (currpath == NULL || argpath == NULL)
		return (NULL);
	newpath = ft_strnew(ft_strlen(currpath) + ft_strlen(argpath) + 1);
	if (newpath == NULL)
		return (NULL);
	if (*argpath == '/')
		*newpath = '/';
	else
		ft_strcpy(newpath, currpath);
	builtin_cd_create_newpath(&newpath, argpath);
	return (newpath);
}
