/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_max.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:36:25 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/18 17:08:16 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

t_tree_node	*__find_max_tr__(t_tree_node *root)
{
	if (root == NULL || !root->right)
		return (root);
	else
		return (__find_max_tr__(root->right));
}

t_tree_node	*find_max_tr(t_bs_tree_ptr tree)
{
	if (empty_tr(tree))
		return (NULL);
	return (__find_max_tr__(tree->root));
}
