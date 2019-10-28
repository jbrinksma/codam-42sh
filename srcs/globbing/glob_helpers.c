/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_helpers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 11:47:38 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/21 14:43:36 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		glob_delmatchlst_ret_err(t_globmatchlst **matchlst)
{
	glob_del_matchlst(matchlst);
	return (FUNCT_ERROR);
}

/*
**	As long as there are tokens with / ./ or ../ they are string joined to path
*/

int		glob_add_dotslash_to_path(t_globtoken **tokenlst, char **path)
{
	if (*path == NULL)
	{
		*path = ft_strnew(0);
		if (*path == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	}
	while (*tokenlst != NULL && ((*tokenlst)->tk_type == GLOB_DOTDOTSLASH ||
		(*tokenlst)->tk_type == GLOB_DOTSLASH ||
		(*tokenlst)->tk_type == GLOB_SLASH))
	{
		*path = ft_strjoinfree_s1(*path, ((*tokenlst)->word_chunk));
		if (*path == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
		*tokenlst = (*tokenlst)->next;
	}
	return (FUNCT_SUCCESS);
}

int		glob_is_dir(char *match, char *path)
{
	char	*filepath;
	int		ret;

	filepath = ft_strjoin(path, match);
	if (filepath == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	ret = ft_isdir(filepath);
	ft_strdel(&filepath);
	if (ret == true)
		return (FUNCT_SUCCESS);
	return (FUNCT_FAILURE);
}

bool	glob_check_hidden_file(t_globtoken *tokenlst)
{
	if (tokenlst == NULL)
		return (false);
	if (tokenlst->tk_type == GLOB_STR && tokenlst->word_chunk[0] == '.')
		return (true);
	return (false);
}

/*
**	glob_keep_dirs removes all non directory files from the matchlst
*/

int		glob_keep_dirs(t_globmatchlst **matchlst, char *path)
{
	t_globmatchlst *matchprobe;
	t_globmatchlst *next;

	if (*matchlst == NULL)
		return (FUNCT_ERROR);
	matchprobe = *matchlst;
	while (matchprobe->next != NULL)
	{
		if (glob_is_dir(matchprobe->next->word, path) != FUNCT_SUCCESS)
		{
			next = matchprobe->next->next;
			glob_delmatch(&matchprobe->next);
			matchprobe->next = next;
		}
		else
			matchprobe = matchprobe->next;
	}
	if (glob_is_dir((*matchlst)->word, path) != FUNCT_SUCCESS)
	{
		next = (*matchlst)->next;
		glob_delmatch(matchlst);
		*matchlst = next;
	}
	return (FUNCT_SUCCESS);
}
