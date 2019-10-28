/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 17:38:55 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/22 11:29:57 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void		reset_glob_scanner(t_globscanner *scanner)
{
	scanner->tk_len = 0;
	scanner->tk_type = GLOB_ERROR;
	scanner->flags = 0;
}

int				glob_add_scanned_token(t_globtoken **lst,
				t_globscanner *scanner)
{
	t_globtoken		*new;
	int				tk_start;
	char			*word_chunk;

	tk_start = scanner->word_index - scanner->tk_len;
	if (tk_start < 0 || scanner->tk_type == GLOB_ERROR || scanner->tk_len < 1)
	{
		ft_eprintf(E_BAD_PATTERN, scanner->word);
		return (FUNCT_ERROR);
	}
	word_chunk = ft_strndup(&scanner->word[tk_start], scanner->tk_len);
	if (word_chunk == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	new = glob_tokenlstnew(word_chunk, scanner->tk_type);
	if (new == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	glob_tokenlstadd(lst, new);
	return (FUNCT_SUCCESS);
}

int				glob_lexer(t_globtoken **lst, char *word)
{
	t_globscanner		*scanner;

	scanner = (t_globscanner*)ft_memalloc(sizeof(t_globscanner));
	if (scanner == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	scanner->word = word;
	while (GLOB_CUR_CHAR != '\0')
	{
		glob_lexer_state_start(scanner);
		if (glob_add_scanned_token(lst, scanner) == FUNCT_ERROR)
		{
			free(scanner);
			return (FUNCT_ERROR);
		}
		reset_glob_scanner(scanner);
	}
	free(scanner);
	if (*lst == NULL)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
