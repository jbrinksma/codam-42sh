/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 05:29:59 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/08 16:42:17 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(char *str, char c)
{
	int		index;
	char	*result;

	index = 0;
	while (str[index] != c && str[index] != '\0')
		index++;
	result = ft_strnew(index + 1);
	if (result == NULL)
		return (NULL);
	index = 0;
	while (str[index] != c && str[index] != '\0')
	{
		result[index] = str[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}
