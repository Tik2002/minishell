/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:05:53 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/15 17:05:34 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <as_tree.h>

void	delete_node_as_tr(t_as_tree_node **root)
{
	(*root)->cmd_mtx = NULL;
	(*root)->left = NULL;
	(*root)->right = NULL;
	free(*root);
	*root = NULL;
}

static void	__clear_tr__(t_as_tree_node *root)
{
	if (!root)
		return ;
	__clear_tr__(root->left);
	__clear_tr__(root->right);
	delete_node_as_tr(&root);
}

void	clear_as_tr(t_as_tree_ptr tree)
{
	if (tree)
		__clear_tr__(tree->root);
}
