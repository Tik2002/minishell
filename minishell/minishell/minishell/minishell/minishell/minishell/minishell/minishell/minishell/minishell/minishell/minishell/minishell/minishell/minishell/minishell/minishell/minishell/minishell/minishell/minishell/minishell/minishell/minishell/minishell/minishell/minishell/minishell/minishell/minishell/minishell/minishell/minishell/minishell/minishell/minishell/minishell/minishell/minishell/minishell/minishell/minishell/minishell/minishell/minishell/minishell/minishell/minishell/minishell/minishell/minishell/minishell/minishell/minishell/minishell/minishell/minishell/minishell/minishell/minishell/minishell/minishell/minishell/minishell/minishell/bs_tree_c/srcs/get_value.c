/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:18:07 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/18 17:08:38 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

char	*get_tr(t_bs_tree_ptr tree, char *key)
{
	t_tree_node	*node;

	if (empty_tr(tree))
		return (NULL);
	node = find_tr(tree, key);
	if (!node)
		return (NULL);
	return (node->val);
}
