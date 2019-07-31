/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_prompt.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 20:16:38 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/31 18:19:23 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	shell_display_prompt(t_envlst *envlst)
{
	char *cwd;
	char *lastdir;
	char *arrow;

	cwd = env_getvalue("PWD", envlst);
	if (g_state->exit_code == EXIT_SUCCESS)
		arrow = YEL "> ";
	else
		arrow = RED "> ";
	lastdir = shell_getcurrentdir(cwd);
	if (lastdir == NULL)
		ft_printf(RED "vsh %s" RESET, arrow);
	else
		ft_printf(RED "vsh " BLU "%s %s" RESET, lastdir, arrow);
}
