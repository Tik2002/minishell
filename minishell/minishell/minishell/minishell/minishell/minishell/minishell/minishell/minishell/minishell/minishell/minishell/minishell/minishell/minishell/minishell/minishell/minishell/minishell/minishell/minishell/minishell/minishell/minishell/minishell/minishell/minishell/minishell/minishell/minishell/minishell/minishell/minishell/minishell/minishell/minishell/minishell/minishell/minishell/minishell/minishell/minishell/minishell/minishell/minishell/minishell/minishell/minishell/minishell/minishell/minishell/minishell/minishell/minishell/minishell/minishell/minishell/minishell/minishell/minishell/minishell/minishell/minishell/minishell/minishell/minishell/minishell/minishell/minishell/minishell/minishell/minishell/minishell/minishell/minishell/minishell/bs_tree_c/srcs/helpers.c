/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:47:08 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/18 17:13:08 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

int	strcmp_tr(char const *s1, char const *s2)
{
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (*s2);
	else if (!s2)
		return (*s1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

t_tree_node	*make_node_tr(char *key, char *val, bool flag)
{
	t_tree_node	*node;

	node = wrapper_malloc(sizeof(t_tree_node));
	node->left = NULL;
	node->right = NULL;
	if (key)
		node->key = ft_strdup(key);
	else
		node->key = ft_strdup("");
	if (val)
		node->val = ft_strdup(val);
	else
		node->val = ft_strdup("");
	node->equal_ma = flag;
	return (node);
}

bool	empty_tr(t_bs_tree_ptr tree)
{
	return (!tree || !tree->root);
}

void	delete_node_tr(t_tree_node **root)
{
	free((*root)->key);
	free((*root)->val);
	(*root)->key = NULL;
	(*root)->val = NULL;
	(*root)->left = NULL;
	(*root)->right = NULL;
	free(*root);
	*root = NULL;
}
