/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:40:52 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 12:29:07 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

t_bs_tree_ptr	init_tr(void)
{
	t_bs_tree_ptr	tree;

	tree = wrapper_malloc(sizeof(t_bs_tree));
	tree->root = NULL;
	tree->size = 0;
	return (tree);
}

static void	insert_tr(t_bs_tree_ptr tree, char *key, char *val, bool flag)
{
	t_tree_node	*y;
	t_tree_node	*x;

	if (empty_tr(tree))
	{
		tree->root = make_node_tr(key, val, flag);
		return ;
	}
	x = tree->root;
	while (x != NULL)
	{
		y = x;
		if (strcmp_tr(x->key, key) > 0)
			x = x->left;
		else if (strcmp_tr(key, x->key) > 0)
			x = x->right;
	}
	x = make_node_tr(key, val, flag);
	if (strcmp_tr(x->key, y->key) > 0)
		y->right = x;
	else
		y->left = x;
}

void	update_tr(t_bs_tree_ptr tree, char *key, char *val, bool flag)
{
	t_tree_node	*tmp;

	tmp = find_tr(tree, key);
	if (tmp)
	{
		free(tmp->val);
		if (!val || !*val)
			tmp->val = ft_strdup("");
		else
			tmp->val = ft_strdup(val);
		tmp->equal_ma = flag;
	}
	else
	{
		insert_tr(tree, key, val, flag);
		tree->size++;
	}
}
