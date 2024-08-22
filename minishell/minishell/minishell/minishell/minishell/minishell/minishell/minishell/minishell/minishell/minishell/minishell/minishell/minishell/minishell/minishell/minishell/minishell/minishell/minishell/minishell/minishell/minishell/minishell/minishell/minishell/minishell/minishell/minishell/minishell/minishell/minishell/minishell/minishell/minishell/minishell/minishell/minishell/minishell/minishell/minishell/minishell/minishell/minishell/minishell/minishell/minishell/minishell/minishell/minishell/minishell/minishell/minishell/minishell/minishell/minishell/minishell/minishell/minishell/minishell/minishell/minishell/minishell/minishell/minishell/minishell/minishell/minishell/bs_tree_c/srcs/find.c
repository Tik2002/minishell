/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:21:53 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/18 17:08:28 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

t_tree_node	*find_tr(t_bs_tree_ptr tree, char *key)
{
	t_tree_node	*tmp;
	int			diff;

	if (empty_tr(tree))
		return (NULL);
	tmp = tree->root;
	while (tmp)
	{
		diff = strcmp_tr(tmp->key, key);
		if (diff == 0)
			return (tmp);
		else if (diff < 0)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	return (NULL);
}
