/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decorator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:49:18 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/18 17:08:09 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

void	__print_env__(t_tree_node *root)
{
	if (root->equal_ma)
		printf("%s=%s\n", root->key, root->val);
}

void	__print_exp__(t_tree_node *root)
{
	if (root->equal_ma)
		printf("declare -x %s=\"%s\"\n", root->key, root->val);
	else
		printf("declare -x %s\n", root->key);
}
