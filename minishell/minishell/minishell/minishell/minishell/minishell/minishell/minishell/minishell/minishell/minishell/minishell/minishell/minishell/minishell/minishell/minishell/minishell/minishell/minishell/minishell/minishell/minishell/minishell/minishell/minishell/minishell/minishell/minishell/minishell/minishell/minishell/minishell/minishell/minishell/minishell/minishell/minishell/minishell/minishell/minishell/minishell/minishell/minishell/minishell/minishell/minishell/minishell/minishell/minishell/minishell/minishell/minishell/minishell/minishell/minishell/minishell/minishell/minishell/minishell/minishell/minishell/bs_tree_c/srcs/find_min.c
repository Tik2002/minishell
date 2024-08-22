/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_min.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:36:42 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/18 17:08:22 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

t_tree_node	*__find_min_tr__(t_tree_node *root)
{
	if (root == NULL || !root->left)
		return (root);
	else
		return (__find_min_tr__(root->left));
}

t_tree_node	*find_min_tr(t_bs_tree_ptr tree)
{
	if (empty_tr(tree))
		return (NULL);
	return (__find_min_tr__(tree->root));
}
