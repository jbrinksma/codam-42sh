/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_debug.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 21:13:37 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/13 14:16:55 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <stdio.h>

/* static void		tree_print_rec(t_ast *root, int depth, int width, int is_child, char ***lines)
{
	if (is_child == true)
	{
		if (root->type == WORD || root->type == ASSIGN)
			(*lines)[depth] = ft_strjoin(root->value, (*lines)[depth]);
		else
			(*lines)[depth] = ft_strjoin(parser_return_token_str(root->type), (*lines)[depth]);
	}
	else
	{
		if (root->type == WORD || root->type == ASSIGN)
			(*lines)[depth] = ft_strjoin((*lines)[depth], root->value);
		else
			(*lines)[depth] = ft_strjoin((*lines)[depth], parser_return_token_str(root->type));
	}

	if (root->sibling)
	{
		(*lines)[depth] = ft_strjoin((*lines)[depth], " -- ");
		tree_print_rec(root->sibling, depth, width + 1, false, lines);
	}

	if (root->child)
	{
		depth++;
		(*lines)[depth] = ft_strjoin("|   ", (*lines)[depth]);
		tree_print_rec(root->child, depth + 1, width, true, lines);
	}
}

void			print_tree(t_ast *root)
{
	char **array;
	int i;

	array = ft_memalloc(sizeof(char*) * 1000);
	i = 0;
	while (i < 999)
	{
		array[i] = ft_strnew(0);
		i++;
	}
	array[i] = NULL;
	ft_putstr("\n\nTREE:\n");
	tree_print_rec(root, 0, 0, false, &array);
	i = 0;
	while (i < 10)
	{
		ft_putendl(array[i]);
		i++;
	}
	ft_putendl("END OF TREE");
	ft_putchar('\n');
} */

// static int		get_tree_height(t_ast *root)
// {
// 	int lh;
// 	int rh;

// 	if (root == NULL)
// 		return (0);
// 	if (root->type != END)
// 	{
// 		lh = get_tree_height(root->child);
// 		rh = get_tree_height(root->sibling);
// 		return (1 + ((lh > rh) ? lh : rh));
// 	}
// 	else
// 		return (1);
// }

static void		get_tree_width(t_ast *root, int *l_width)
{
	int width;

	if (!root)
		return ;
	if (root->type == WORD)
	{
		width = ft_strlen(root->value);
		width > *l_width ? *l_width = width : 0;
	}
	if (root->child != NULL)
		get_tree_width(root->child, l_width);
	if (root->sibling != NULL)
		get_tree_width(root->sibling, l_width);
}

static void		print_color(int color)
{
	if (color == 0)
		printf("\e[0;31m");
	if (color == 1)
		printf("\e[0;32m");
	if (color == 2)
		printf("\e[0;33m");
	if (color == 3)
		printf("\e[0;34m");
	if (color == 4)
		printf("\e[0;35m");
	if (color == 5)
		printf("\e[0;36m");
	if (color == 6)
		printf("\e[0;37m");
}

static void		tree_print_rec(t_ast *root, int depth, int space, int width)
{
	int i;

	if (!root)
		return ;
	space += width;
	if (root->sibling != NULL)
		tree_print_rec(root->sibling, depth + 1, space, width);
	i = width;
	while (i < space)
	{
		ft_putchar(' ');
		i++;
	}
	print_color(depth % 7);
	if (root->type == WORD || root->type == ASSIGN)
		printf("%s\e[0m\n", root->value);
	else
		printf("%s\e[0m\n", parser_return_token_str(root->type));
	if (root->child != NULL)
		tree_print_rec(root->child, depth + 1, space, width);
}

void			print_tree(t_ast *root)
{
	int width;

	width = 4;
	if (!root)
		return ;
	printf("\n>>>> TREE <<<<\n");
	get_tree_width(root, &width);
	tree_print_rec(root, 0, 0, width);
	printf("\n>>>> END TREE <<<<\n\n");
}