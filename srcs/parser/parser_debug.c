/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_debug.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 21:13:37 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/05 13:21:34 by mavan-he      ########   odam.nl         */
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

	if (root->right)
	{
		(*lines)[depth] = ft_strjoin((*lines)[depth], " -- ");
		tree_print_rec(root->right, depth, width + 1, false, lines);
	}

	if (root->left)
	{
		depth++;
		(*lines)[depth] = ft_strjoin("|   ", (*lines)[depth]);
		tree_print_rec(root->left, depth + 1, width, true, lines);
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
// 		lh = get_tree_height(root->left);
// 		rh = get_tree_height(root->right);
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
	if (root->left != NULL)
		get_tree_width(root->left, l_width);
	if (root->right != NULL)
		get_tree_width(root->right, l_width);
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
	if (root->right != NULL)
		tree_print_rec(root->right, depth + 1, space, width);
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
	if (root->left != NULL)
		tree_print_rec(root->left, depth + 1, space, width);
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
