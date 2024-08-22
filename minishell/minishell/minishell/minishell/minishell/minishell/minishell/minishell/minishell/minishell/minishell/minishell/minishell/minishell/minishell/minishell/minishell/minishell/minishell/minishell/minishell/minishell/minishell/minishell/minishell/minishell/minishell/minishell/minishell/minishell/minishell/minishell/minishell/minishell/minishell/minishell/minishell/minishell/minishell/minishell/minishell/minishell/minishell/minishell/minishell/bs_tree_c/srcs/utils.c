/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:44:21 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/18 17:15:21 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

void	swap_tr(t_tree_node *left, t_tree_node *right)
{
	char	*val;
	char	*key;

	if (!left || !right)
		return ;
	val = left->val;
	key = left->key;
	left->key = right->key;
	left->val = right->val;
	right->val = val;
	right->key = key;
}
