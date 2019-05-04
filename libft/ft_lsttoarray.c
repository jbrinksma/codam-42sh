/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lsttoarray.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/04 15:31:16 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/04 16:52:47 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lsttoarray(t_list *lst)
{
	int		len;
	char	**array;
	int		i;

	if (lst == NULL)
		return (NULL);
	len = ft_lstlen(lst);
	array = (char**)ft_memalloc(sizeof(char*) * (len + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (lst)
	{
		array[i] = ft_strdup(lst->content);
		if (array[i] == NULL)
			return (NULL);
		i++;
		lst = lst->next;
	}
	return (array);
}
