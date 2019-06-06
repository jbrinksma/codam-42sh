/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 10:21:20 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/06/05 17:08:36 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static char	builtin_echo_replacespecial(char c)
{
	if (c == 'a')
		return ('\a');
	if (c == 'b')
		return (BS);
	if (c == 'e' || c == 'E')
		return (ESC);
	if (c == 'f')
		return ('\f');
	if (c == 'n')
		return ('\n');
	if (c == 'r')
		return ('\r');
	if (c == 't')
		return ('\t');
	if (c == 'v')
		return ('\v');
	if (c == '\\')
		return ('\\');
	return (0);
}

static void	builtin_echo_escape_chars(char *arg)
{
	int		i;
	int		i_new;
	char	replace_char;

	i = 0;
	i_new = 0;
	while (arg[i] != '\0')
	{
		replace_char = builtin_echo_replacespecial(arg[i + 1]);
		if (arg[i] == '\\' && replace_char != 0)
		{
			i++;
			arg[i_new] = replace_char;
		}
		else
			arg[i_new] = arg[i];
		i_new++;
		i++;
	}
	while (arg[i_new] != '\0')
	{
		arg[i_new] = '\0';
		i_new++;
	}
}

/*
** ECHO:
** Output the args, seperated by spaces, followed by a newline.
** If -n is specified, the trailing newline is not printed.
** The -e option will enable interpretation of the following escape characters:
** \a \b \E \e \f \n \r \t \v \\.
** Option -E disables interpretation of escape characters.
*/

void		builtin_echo(char **args, int *exit_code)
{
	int		arg_i;
	char	flags;

	arg_i = 1;
	flags = builtin_echo_set_flags(args, &arg_i);
	while (args[arg_i])
	{
		if (flags & ECHO_OPT_EL)
			builtin_echo_escape_chars(args[arg_i]);
		ft_putstr(args[arg_i]);
		if (args[arg_i + 1] != NULL)
			ft_putchar(' ');
		arg_i++;
	}
	if ((flags & ECHO_OPT_NL) == 0)
		ft_putchar('\n');
	*exit_code = EXIT_SUCCESS;
}
