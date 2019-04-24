/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_update_quote_status.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 13:23:35 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/24 13:58:10 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	test_update_quote_status_basic(void)
{
	char quote;

	quote = '\0';
	if (update_quote_status("easy\"line\"", 3, &quote) != 0 || quote != '\0')
		return (FUNCT_FAILURE);
	quote = '\0';
	if (update_quote_status("easy\"line\"", 4, &quote) != 1 || quote != '"')
		return (FUNCT_FAILURE);
	quote = '\0';
	if (update_quote_status("easy\"line\"", 5, &quote) != 0 || quote != '\0')
		return (FUNCT_FAILURE);
	quote = '\0';
	if (update_quote_status("easy'line'", 3, &quote) != 0 || quote != '\0')
		return (FUNCT_FAILURE);
	quote = '\0';
	if (update_quote_status("easy'line'", 4, &quote) != 1 || quote != '\'')
		return (FUNCT_FAILURE);
	quote = '\0';
	if (update_quote_status("easy'line'", 5, &quote) != 0 || quote != '\0')
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

static int	test_update_quote_status_harder(void)
{
	char quote;

	quote = '\'';
	if (update_quote_status("h'arde\\'rline'", 7, &quote) != 0 || quote != '\'')
		return (FUNCT_FAILURE);
	quote = '\0';
	if (update_quote_status("\\'harderline", 1, &quote) != 0 || quote != '\0')
		return (FUNCT_FAILURE);
	quote = '\"';
	if (update_quote_status("\"harder'line\"", 7, &quote) != 0 || quote != '"')
		return (FUNCT_FAILURE);
	quote = '\0';
	if (update_quote_status("\\\"harder'line", 8, &quote) != 1 || quote != '\'')
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

int			test_update_quote_status(void)
{
	if (test_update_quote_status_basic() != FUNCT_SUCCESS)
		return (FUNCT_FAILURE);
	if (test_update_quote_status_harder() != FUNCT_SUCCESS)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
