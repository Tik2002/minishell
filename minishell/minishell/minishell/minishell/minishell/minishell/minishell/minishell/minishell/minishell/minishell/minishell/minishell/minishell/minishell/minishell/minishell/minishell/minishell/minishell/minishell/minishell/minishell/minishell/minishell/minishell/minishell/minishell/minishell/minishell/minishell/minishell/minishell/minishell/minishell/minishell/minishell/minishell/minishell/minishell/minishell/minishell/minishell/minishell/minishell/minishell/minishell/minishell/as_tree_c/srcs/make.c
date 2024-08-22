/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:15:11 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/21 17:37:09 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <as_tree.h>

t_as_tree_node	*make_as_node_tr(t_as_tree_node *node, t_cmd_matrix *cmd_mtx,
		t_node_type node_type)
{
	t_as_tree_node	*root;

	root = wrapper_malloc(sizeof(t_as_tree_node));
	root->cmd_mtx = cmd_mtx;
	root->left = node;
	root->right = NULL;
	root->node_type = node_type;
	return (root);
}

static t_as_tree_node	*make_as_root_tr(t_cmd_matrix *cmd_mtx)
{
	t_as_tree_node	*root;

	root = wrapper_malloc(sizeof(t_as_tree_node));
	root->cmd_mtx = cmd_mtx;
	root->left = NULL;
	root->right = NULL;
	root->node_type = COMMAND;
	return (root);
}

t_as_tree_ptr	init_as_tr(t_cmd_matrix *cmd_mtx)
{
	t_as_tree_ptr	tree;

	tree = wrapper_malloc(sizeof(t_as_tree));
	tree->root = make_as_root_tr(cmd_mtx);
	return (tree);
}
