/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_expand_word.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/07 14:54:03 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/21 13:26:26 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	glob_init_path sets the start path of the WORD we need to expand
**	If there is no ./ or ../ or slash we get the cwd
**	In this case we also set cwd_len to the lenght of the cwd
**	Otherwise glob_add_dotslash_to_path will set path and cwd_len remains zero
*/

static int	glob_init_path(t_globtoken **tokenlst, char **path, int *cwd_len)
{
	if ((*tokenlst)->tk_type == GLOB_SLASH ||
		(*tokenlst)->tk_type == GLOB_DOTSLASH ||
		(*tokenlst)->tk_type == GLOB_DOTDOTSLASH)
	{
		if (glob_add_dotslash_to_path(tokenlst, path) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	else
	{
		*path = getcwd(NULL, 0);
		if (*path == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
		*path = ft_strjoinfree_s1(*path, "/");
		*cwd_len = ft_strlen(*path);
	}
	if (*path == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	return (FUNCT_SUCCESS);
}

static void	glob_free(t_globtoken **tokenlst, char **path)
{
	glob_del_tokenlst(tokenlst);
	ft_strdel(path);
}

/*
**	Glob pathname expansion starts with the lexer which creates a tokenlst.
**	It will then init the path variable.
**	If that is all successful, we go into the glob_dir_match_loop
*/

int			glob_expand_word(t_glob *glob_data, char *word)
{
	t_globtoken		*tokenlst;
	t_globtoken		*tokenlst_head;
	char			*path;

	if (word == NULL)
		return (FUNCT_ERROR);
	path = NULL;
	tokenlst = NULL;
	if (glob_lexer(&tokenlst, word) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	tokenlst_head = tokenlst;
	if (glob_init_path(&tokenlst, &path, &glob_data->cwd_len) == FUNCT_ERROR)
	{
		glob_free(&tokenlst_head, &path);
		return (FUNCT_ERROR);
	}
	if (glob_dir_match_loop(glob_data, tokenlst, path) == FUNCT_ERROR)
	{
		glob_free(&tokenlst_head, &path);
		return (FUNCT_ERROR);
	}
	glob_free(&tokenlst_head, &path);
	return (FUNCT_SUCCESS);
}
