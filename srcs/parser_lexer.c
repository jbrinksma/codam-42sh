/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_lexer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:57:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/17 18:29:50 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

// static int	get_total_commands(char *line)
// {
// 	int index;
// 	int	total;

// 	index = 0;
// 	return (total);
// }

// static int	get_total_args(char *line)
// {
// 	int index;
// 	int total;

// 	index = 0;
// 	total = 0;
// 	while (line[index] != '\0')
// 	{
// 		if (line[index] == ';' && line[index - 1] != '\\')
// 		total++;
// 	}
// 	return (total);
// }

// static char *init_cmdtab_arg(char *line, int start)
// {
// 	char	*cmdtab_arg;
// 	int		arglen;
// 	int		index;

// 	arglen = get_total_args(&line[start]);
// 	cmdtab_arg = (char**)malloc(sizeof(char*) * (arglen + 1));
// 	index = 0;
// 	while (index < arglen)
// 	{
// 		cmdtab_arg[index] = line[start];
// 		index++;
// 		start++;
// 	}
// 	cmdtab_arg[index] = NULL;
// }

// static char	**init_cmdtab_args(char *line, int start)
// {
// 	char	**cmdtab_args;
// 	int		total_args;
// 	int		index;

// 	total_args = get_total_args(&line[start]);
// 	cmdtab_args = (char**)malloc(sizeof(char*) * (total_args + 1));
// 	index = 0;
// 	while (index < total_args)
// 	{
// 		cmdtab_args[index] = 
// 		index++;
// 	}
// 	cmdtab_args[index] = NULL;
// }

// static int	get_next_command_index(char *line, int start)
// {
// 	while (line[start] != '\0')
// 	{
// 		start++;
// 		/* fix this for escaped escape */
// 		if (line[start] == ';' && line[start - 1] != '\\')
// 			return (start);
// 	}
// 	return (start);
// }

// static char	***init_cmdtab_commands(char *line)
// {
// 	char	***cmdtab;
// 	int		total_commands;
// 	int		index;
// 	int		start;

// 	total_commands = get_total_commands(line);
// 	cmdtab = (char***)malloc(sizeof(char**) * (total_commands + 1));
// 	index = 0;
// 	start = 0;
// 	while (index < total_commands)
// 	{
// 		cmdtab[index] = init_cmdtab_args(line, start);
// 		index++;
// 		start = get_next_command_index(line, start);
// 	}
// 	cmdtab[index] = NULL;
// }

// int			parser_lexer(char ****cmdtab, char *line)
// {
// 	*cmdtab = init_cmdtab_commands(line);
// 	return (FUNCT_SUCCESS);
// }
