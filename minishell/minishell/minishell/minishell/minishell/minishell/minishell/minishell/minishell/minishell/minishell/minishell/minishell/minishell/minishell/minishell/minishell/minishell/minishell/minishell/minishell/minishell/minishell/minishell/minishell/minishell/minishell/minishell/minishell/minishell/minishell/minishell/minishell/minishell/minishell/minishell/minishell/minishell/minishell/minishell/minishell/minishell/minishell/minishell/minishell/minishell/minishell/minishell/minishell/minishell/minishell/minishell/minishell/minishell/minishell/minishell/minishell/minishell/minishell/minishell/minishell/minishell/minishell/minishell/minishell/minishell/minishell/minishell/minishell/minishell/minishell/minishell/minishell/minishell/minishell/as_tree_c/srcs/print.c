/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:59:30 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/21 17:37:14 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <as_tree.h>

static void	__print_util__(t_as_tree_node *root)
{
	if (!root)
		return ;
	__print_util__(root->left);
	printf("%d\n", root->node_type);
	__print_util__(root->right);
}

void	print_as_tr(t_as_tree_ptr tree)
{
	__print_util__(tree->root);
}
