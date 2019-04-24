/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_is_char_escaped.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/23 20:20:01 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 20:29:07 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	test_is_char_escaped_harder(void)
{
	if (is_char_escaped("\\\"\\n", 3) != FUNCT_SUCCESS)
		return (FUNCT_FAILURE);
	if (is_char_escaped("\\\"\\\\n", 4) != FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	if (is_char_escaped("", 0) != FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

static int	test_is_char_escaped_basic(void)
{
	if (is_char_escaped("\\n", 1) != FUNCT_SUCCESS)
		return (FUNCT_FAILURE);
	if (is_char_escaped("\\\\n", 2) != FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	if (is_char_escaped("abc\\n", 4) != FUNCT_SUCCESS)
		return (FUNCT_FAILURE);
	if (is_char_escaped("abc\\\\n", 5) != FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

int			test_is_char_escaped(void)
{
	if (test_is_char_escaped_basic() != FUNCT_SUCCESS)
		return (FUNCT_FAILURE);
	if (test_is_char_escaped_harder() != FUNCT_SUCCESS)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
