/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:24:58 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/18 17:12:08 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

static void	__print_util__(t_tree_node *root, t_decorator f)
{
	if (!root)
		return ;
	__print_util__(root->left, f);
	f(root);
	__print_util__(root->right, f);
}

void	print_tr(t_bs_tree_ptr tree)
{
	__print_util__(tree->root, __print_env__);
}

void	print_tr_custom(t_bs_tree_ptr tree, t_decorator f)
{
	__print_util__(tree->root, f);
}
