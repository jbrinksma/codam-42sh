/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_debug.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 21:13:37 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/31 14:53:42 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <stdio.h>

static int		get_tree_height(t_ast *root)
{
	int lh;
	int rh;

	if (root == NULL)
		return (0);
	if (root->type != END)
	{
		lh = get_tree_height(root->child);
		rh = get_tree_height(root->sibling);
		return (1 + ((lh > rh) ? lh : rh));
	}
	else
		return (1);
}

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
	int height;

	width = 4;
	if (!root)
		return ;
	height = get_tree_height(root);
	printf("Tree height: %d\n", height);
	get_tree_width(root, &width);
	tree_print_rec(root, 0, 0, width);
}
