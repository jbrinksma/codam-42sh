/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_dir_match_loop.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 18:19:03 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/21 14:39:34 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <dirent.h>

/*
**	glob_getmatchlist opens the directory pointed to by path
**	each entry is added to the matchlst
**	if hidden_file is true it also adds hidden files to the lst
*/

static int	glob_getmatchlist(t_globmatchlst **matchlst, char *path,
			bool hidden_file)
{
	DIR				*dir;
	struct dirent	*rdir;

	dir = opendir(path);
	if (dir == NULL)
		return (FUNCT_FAILURE);
	rdir = readdir(dir);
	while (rdir != NULL)
	{
		if ((ft_strequ(rdir->d_name, ".") || ft_strequ(rdir->d_name, ".."))
		== false && (rdir->d_name[0] == '.' && hidden_file == false) == false)
		{
			if (glob_matchlstadd(matchlst, rdir->d_name) == FUNCT_ERROR)
			{
				closedir(dir);
				return (FUNCT_ERROR);
			}
		}
		rdir = readdir(dir);
	}
	closedir(dir);
	return (FUNCT_SUCCESS);
}

/*
**	For each potential match in matchlst we call glob_matcher
**	If there is a match we keep it in the lst, otherwise it is deleted
*/

void		glob_start_matching(t_globtoken *tokenlst,
			t_globmatchlst **matchlst)
{
	t_globmatchlst *matchprobe;
	t_globmatchlst *next;

	if (*matchlst == NULL)
		return ;
	matchprobe = *matchlst;
	while (matchprobe->next != NULL)
	{
		if (glob_matcher(tokenlst, *(matchprobe->next)) != FUNCT_SUCCESS)
		{
			next = matchprobe->next->next;
			glob_delmatch(&matchprobe->next);
			matchprobe->next = next;
		}
		else
			matchprobe = matchprobe->next;
	}
	if (glob_matcher(tokenlst, **matchlst) != FUNCT_SUCCESS)
	{
		next = (*matchlst)->next;
		glob_delmatch(matchlst);
		*matchlst = next;
	}
}

/*
**	If tokenlst is NULL we are at the end so we add path to expanded lst
**	otherwise we call another glob_dir_match_loop
*/

static int	glob_add_match_or_continue(t_glob *glob_data, t_globtoken *tokenlst,
			char *path)
{
	if (tokenlst != NULL)
	{
		if (glob_dir_match_loop(glob_data, tokenlst, path) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	else
	{
		if (glob_ast_add_left(&glob_data->expanded, &path[glob_data->cwd_len],
			WORD, 0) == FUNCT_ERROR)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	}
	return (FUNCT_SUCCESS);
}

/*
**	First we create the path suffix (any slash or ./ ../)
**	For each match in matchlst we join "path" "match" "path suffix" together
**	and check if we need to add it to the expanded lst or continue with
**	another glob_dir_match_loop
*/

static int	glob_handle_matchlst(t_globmatchlst *matchlst,
			t_glob *glob_data, t_globtoken *tokenlst, char *path)
{
	char			*path_suffix;
	char			*new_path;

	path_suffix = NULL;
	if (glob_add_dotslash_to_path(&tokenlst, &path_suffix) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	while (matchlst != NULL)
	{
		new_path = ft_strjoinfree_s2(path, ft_strjoin(matchlst->word,
		path_suffix));
		if (new_path == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
		if (glob_add_match_or_continue(glob_data, tokenlst, new_path)
			== FUNCT_ERROR)
		{
			ft_strdel(&new_path);
			ft_strdel(&path_suffix);
			return (FUNCT_ERROR);
		}
		ft_strdel(&new_path);
		matchlst = matchlst->next;
	}
	ft_strdel(&path_suffix);
	return (FUNCT_SUCCESS);
}

/*
**	First we get the matchlst (all files in the directory pointed to by path)
**	glob_start_matching finds all matches
**	If the tokenlst is not at the end, we keep every match that is a direcotry
**	We then continue the same loop again with each matching directory
**	If tokenlst is at end, all remaining matches are added to the expanded lst
*/

int			glob_dir_match_loop(t_glob *glob_data, t_globtoken *tokenlst,
			char *path)
{
	t_globmatchlst	*matchlst;
	int				ret;

	matchlst = NULL;
	ret = glob_getmatchlist(&matchlst, path, glob_check_hidden_file(tokenlst));
	if (ret != FUNCT_SUCCESS)
		return (ret);
	glob_start_matching(tokenlst, &matchlst);
	if (matchlst == NULL)
		return (FUNCT_FAILURE);
	while (tokenlst != NULL && tokenlst->tk_type != GLOB_SLASH)
		tokenlst = tokenlst->next;
	if (tokenlst != NULL && glob_keep_dirs(&matchlst, path) == FUNCT_ERROR)
		return (glob_delmatchlst_ret_err(&matchlst));
	ret = glob_handle_matchlst(matchlst, glob_data, tokenlst, path);
	glob_del_matchlst(&matchlst);
	return (ret);
}
