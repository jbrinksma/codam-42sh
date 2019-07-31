/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_getcurrentdir.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/30 17:27:41 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/30 18:23:54 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

char		*shell_getcurrentdir(char *cwd)
{
	int		i;

	i = 0;
	if (cwd == NULL || *cwd == '\0')
		return (NULL);
	if (cwd[0] == '/' && cwd[1] == '\0')
		return (cwd);
	while (cwd[i] != '\0')
		i++;
	while (cwd[i] != '/' && i >= 0)
		i--;
	i++;
	return (&cwd[i]);
}
