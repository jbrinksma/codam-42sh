/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/04 10:16:26 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 21:16:07 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vsh.h>

static size_t	count_args(t_ast *ast)
{
	t_ast	*probe;
	size_t	i;

	i = 0;
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

static char		**create_args(t_ast *ast)
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

static bool		exec_command_contains_only_assign(t_ast *ast)
{
	t_ast	*probe;

	if (ast->type == WORD)
		return (false);
	probe = ast;
	while (probe != NULL)
	{
		if (tool_is_redirect_tk(probe->type) == true)
			return (false);
		probe = probe->left;
	}
	return (true);
}

int				exec_command(t_ast *ast, t_vshdata *data)
{
	char	**argv;

	if (expan_handle_variables(ast, data->envlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ast->type == WORD && expan_pathname(ast) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	exec_quote_remove(ast);
	if (exec_command_contains_only_assign(ast) == false)
	{
		if (ast->type == WORD)
			data->current_redir_and_assign = ast->right;
		else
			data->current_redir_and_assign = ast;
		argv = create_args(ast);
		if (argv == NULL)
			return (FUNCT_ERROR);
		exec_cmd(argv, data);
	}
	if (ast->type != WORD && exec_assigns(ast, data, ENV_LOCAL) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
