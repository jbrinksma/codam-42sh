/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:37:32 by omulder        #+#    #+#                */
/*   Updated: 2019/04/24 12:21:39 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int		test_ret_fail(char *str)
{
	ft_printf("%s\n", str);
	return (EXIT_FAILURE);
}

int		main(void)
{
	if (test_prompt() != FUNCT_SUCCESS)
		return (test_ret_fail("test_prompt failed!"));
	if (test_free_and_return_null() != FUNCT_SUCCESS)
		return (test_ret_fail("test_free_and_return_null failed!"));
	if (test_get_environ_cpy() != FUNCT_SUCCESS)
		return (test_ret_fail("test_get_environ_cpy failed!"));
	if (test_param_to_env() != FUNCT_SUCCESS)
		return (test_ret_fail("test_param_to_env failed!"));
	if (test_term_is_valid() != FUNCT_SUCCESS)
		return (test_ret_fail("test_term_is_valid failed!"));
	if (test_term_init_struct() != FUNCT_SUCCESS)
		return (test_ret_fail("test_term_init_struct failed!"));
	if (test_term_free_struct() != FUNCT_SUCCESS)
		return (test_ret_fail("test_term_free_struct failed!"));
	if (test_term_get_attributes() != FUNCT_SUCCESS)
		return (test_ret_fail("test_term_get_attributes failed!"));
	if (test_parser_split_commands() == FUNCT_FAILURE)
		return (test_ret_fail("test_parser_split_commands failed!"));
	if (test_parser_strdup_command_from_line() == FUNCT_FAILURE)
		return (test_ret_fail("test_parser_strdup_command_from_line failed!"));
	if (test_parser_command_len_from_line() == FUNCT_FAILURE)
		return (test_ret_fail("test_parser_command_len_from_line failed!"));
	if (test_parser_total_commands_from_line() == FUNCT_FAILURE)
		return (test_ret_fail("test_parser_total_commands_from_line failed!"));
	if (test_is_char_escaped() == FUNCT_FAILURE)
		return (test_ret_fail("test_is_char_escaped failed!"));
	return (EXIT_SUCCESS);
}
