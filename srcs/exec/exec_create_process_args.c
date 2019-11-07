/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_create_process_args.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 18:19:28 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/05 10:55:18 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static size_t	count_args(t_ast *ast)
{
	t_ast	*probe;
	size_t	i;

	i = 0;
	if (ast == NULL || ast->type != WORD)
		return (0);
	probe = ast;
	while (probe != NULL && (probe->type == WORD || probe->type == ASSIGN))
	{
		i++;
		probe = probe->left;
	}
	return (i);
}

static char		**malloc_args(int total_args)
{
	char	**args;

	if (total_args > 0)
		args = (char**)ft_memalloc(sizeof(char*) * (total_args + 1));
	else
	{
		args = (char**)ft_memalloc(sizeof(char*) * 2);
		if (args == NULL)
			return (NULL);
		*args = ft_strnew(0);
		if (*args == NULL)
			ft_strarrdel(&args);
	}
	return (args);
}

char			**exec_create_process_args(t_ast *ast)
{
	char	**args;
	t_ast	*probe;
	size_t	total_args;
	size_t	i;

	total_args = count_args(ast);
	args = malloc_args(total_args);
	if (args == NULL)
		return (NULL);
	i = 0;
	probe = ast;
	while (i < total_args)
	{
		args[i] = ft_strdup(probe->value);
		if (args[i] == NULL)
		{
			ft_strarrdel(&args);
			return (NULL);
		}
		probe = probe->left;
		i++;
	}
	return (args);
}
