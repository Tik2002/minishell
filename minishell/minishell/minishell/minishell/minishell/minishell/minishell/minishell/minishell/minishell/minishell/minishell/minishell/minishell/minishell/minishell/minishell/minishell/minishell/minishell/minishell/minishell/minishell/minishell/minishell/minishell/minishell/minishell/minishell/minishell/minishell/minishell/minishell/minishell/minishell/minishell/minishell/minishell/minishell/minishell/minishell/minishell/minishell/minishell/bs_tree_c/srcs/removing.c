/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:56:14 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/19 16:32:49 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

static void	__remove_if_equal_tr__(t_tree_node **root, char *key);

static t_tree_node	*__remove_tr__(t_tree_node *root, char *key)
{
	if (!root)
		return (NULL);
	if (strcmp_tr(root->key, key) > 0)
		root->left = __remove_tr__(root->left, key);
	else if (strcmp_tr(root->key, key) < 0)
		root->right = __remove_tr__(root->right, key);
	else
	{
		__remove_if_equal_tr__(&root, key);
	}
	return (root);
}

static void	__remove_if_equal_tr__(t_tree_node **root, char *key)
{
	t_tree_node	*predecessor;

	if (!(*root)->left && !(*root)->right)
		delete_node_tr(root);
	else if (!(*root)->left && (*root)->right)
	{
		swap_tr(*root, (*root)->right);
		(*root)->right = __remove_tr__((*root)->right, key);
	}
	else if (!(*root)->right && (*root)->left)
	{
		swap_tr(*root, (*root)->left);
		(*root)->left = __remove_tr__((*root)->left, key);
	}
	else
	{
		predecessor = __find_max_tr__((*root)->left);
		swap_tr(predecessor, *root);
		(*root)->left = __remove_tr__((*root)->left, key);
	}
}

void	remove_tr(t_bs_tree_ptr tree, char *key)
{
	if (empty_tr(tree))
		return ;
	tree->size--;
	tree->root = __remove_tr__(tree->root, key);
}

static void	__clear_tr__(t_tree_node *root)
{
	if (!root)
		return ;
	__clear_tr__(root->left);
	__clear_tr__(root->right);
	delete_node_tr(&root);
}

void	clear_tr(t_bs_tree_ptr tree)
{
	__clear_tr__(tree->root);
	tree->size = 0;
}
