/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strreplace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/03 14:51:48 by omulder        #+#    #+#                */
/*   Updated: 2019/04/23 19:38:10 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  Replaces the first occurence of find in str with the contents of replace.
** 	If find is not found in str, returns a copy of str.
*/

char	*ft_strreplace(char *str, char *find, char *replace)
{
	char	*new;
	char	*temp;
	int		len;

	if (!str || !find || !replace)
		return (NULL);
	temp = ft_strstr(str, find);
	if (temp == NULL)
		return (ft_strdup(str));
	len = (int)(temp - str);
	new = ft_strsub(str, 0, len);
	if (new == NULL)
		return (NULL);
	temp = new;
	new = ft_strjoin(temp, replace);
	ft_strdel(&temp);
	if (new == NULL)
		return (NULL);
	temp = new;
	new = ft_strjoin(new, &str[ft_strlen(find) + len]);
	ft_strdel(&temp);
	if (new == NULL)
		return (NULL);
	return (new);
}
