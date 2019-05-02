/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_join_key_value.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 16:00:15 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/02 10:23:48 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

char	*var_join_key_value(char *var_key, char *var_value)
{
	char *var_pair;

	var_pair = ft_strnew(ft_strlen(var_key) + ft_strlen(var_value) + 1);
	if (var_pair == NULL)
		return (NULL);
	ft_strcpy(var_pair, var_key);
	ft_strcat(var_pair, "=");
	ft_strcat(var_pair, var_value);
	return (var_pair);
}
