/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:52:22 by omulder        #+#    #+#                */
/*   Updated: 2019/05/31 10:20:28 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static char	**create_args(t_ast *ast)
{
	char	**args;
	char	*temp;
	t_ast	*probe;

	if (ast == NULL)
		return (NULL);
	args = (char**)ft_memalloc(sizeof(char*) * 2);
	if (args == NULL)
		return (NULL);
	args[0] = ft_strdup(ast->value);
	if (args[0] == NULL)
		return (NULL);
	probe = ast->child;
	while (probe)
	{
		temp = ft_strdup(probe->value);
		if (temp == NULL)
			return (NULL);
		if (ft_strarradd(&args, temp) == FUNCT_ERROR)
			return (NULL);
		probe = probe->child;
	}
	return (args);
}

int			exec_start(t_ast *ast, int *exit_code)
{
	char	**env;
	char	**args;

	env = env_get_environ_cpy();
	if (env == NULL)
		return (FUNCT_FAILURE);
	if (ast->type == WORD)
	{
		args = create_args(ast);
		if (args == NULL)
			return (FUNCT_FAILURE);
		return (exec_cmd(args, &env, exit_code));
	}
	else
	{
		ft_printf("N0p3: I only do the easy shit, don't fuckup!\n");
		return (FUNCT_FAILURE);
	}
}
