/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:14:42 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/21 17:37:05 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <as_tree.h>

void	insert_node_as_tr(t_as_tree_ptr tree, t_cmd_matrix *cmd_mtx,
		t_node_type type, t_priority priority)
{
	t_as_tree_node	*curr;

	if (type == OR || type == AND)
	{
		if (priority == ROOT)
			tree->root = make_as_node_tr(tree->root, cmd_mtx, type);
		else
			tree->root->right = make_as_node_tr(tree->root->right, cmd_mtx,
					type);
	}
	else
	{
		curr = tree->root;
		while (curr->right != NULL)
			curr = curr->right;
		curr->right = make_as_node_tr(curr->right, cmd_mtx, type);
	}
}
