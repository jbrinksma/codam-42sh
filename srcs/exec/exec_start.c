/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:52:22 by omulder        #+#    #+#                */
/*   Updated: 2019/06/06 13:51:14 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static char	**init_array(t_ast *ast)
{
	char	**args;

	if (ast == NULL)
		return (NULL);
	args = (char**)ft_memalloc(sizeof(char*) * 2);
	if (args == NULL)
		return (NULL);
	args[0] = ft_strdup(ast->value);
	if (args[0] == NULL)
	{
		ft_strarrdel(&args);
		return (NULL);
	}
	return (args);
}

static int	add_argument(char ***args, char *value)
{
	char	*temp;

	temp = ft_strdup(value);
	if (temp == NULL)
	{
		ft_strarrdel(args);
		return (FUNCT_FAILURE);
	}
	if (ft_strarradd(args, temp) == FUNCT_FAILURE)
	{
		ft_strdel(&temp);
		ft_strarrdel(args);
		return (FUNCT_FAILURE);
	}
	ft_strdel(&temp);
	return (FUNCT_SUCCESS);
}

static char	**create_args(t_ast *ast)
{
	char	**args;
	t_ast	*probe;

	args = (init_array(ast));
	if (args == NULL)
		return (NULL);
	probe = ast->child;
	while (probe)
	{
		if (add_argument(&args, probe->value) == FUNCT_FAILURE)
			return (NULL);
		probe = probe->child;
	}
	return (args);
}

void		exec_start(t_ast *ast, t_envlst *envlst, int *exit_code)
{
	char	**args;
	char	*assign;

	if (ast->type == WORD)
	{
		args = create_args(ast);
		if (args == NULL)
			return ;
		exec_cmd(args, envlst, exit_code);
	}
	else if (ast->type == ASSIGN)
	{
		assign = ast->value;
		if (assign == NULL)
			return ;
		/* Builtin assign will only take one ASSIGN at a time */	
		builtin_assign(assign, envlst, exit_code);
	}
	else
		ft_printf("N0p3: I only do the easy shit, don't fuckup!\n");
}
