/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:10:09 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/20 16:25:20 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	__eval_container__(t_as_tree_node *root)
{
	if (!root)
		return ;
	__eval_container__(root->left);
	if (root->node_type == OR && !get_status())
		return ;
	if (root->node_type == AND && get_status())
		return ;
	if (root->node_type == COMMAND)
		ft_eval_commands(root->cmd_mtx);
	__eval_container__(root->right);
}

void	ft_eval_container(t_container *container)
{
	__eval_container__(container->as_tree->root);
}
