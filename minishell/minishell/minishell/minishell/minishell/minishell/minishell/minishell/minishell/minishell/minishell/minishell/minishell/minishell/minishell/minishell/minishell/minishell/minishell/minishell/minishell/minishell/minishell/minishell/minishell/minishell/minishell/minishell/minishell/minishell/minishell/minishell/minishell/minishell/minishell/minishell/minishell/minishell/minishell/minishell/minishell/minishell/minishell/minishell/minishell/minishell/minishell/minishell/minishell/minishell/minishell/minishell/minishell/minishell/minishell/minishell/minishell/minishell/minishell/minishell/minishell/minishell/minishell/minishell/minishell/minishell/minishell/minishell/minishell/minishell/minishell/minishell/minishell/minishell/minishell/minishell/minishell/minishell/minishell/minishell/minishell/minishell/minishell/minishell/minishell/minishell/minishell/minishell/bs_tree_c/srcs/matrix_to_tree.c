/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_to_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:19:32 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/18 17:11:23 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

static t_tree_node	*__init__root__(char *line)
{
	t_tree_node	*root;
	char		*key;
	char		*val;
	bool		flag;

	flag = ft_strchr(line, '=');
	val = ft_strchr(line, '=');
	if (!flag)
	{
		root = make_node_tr(line, "", flag);
		return (root);
	}
	key = ft_substr(line, 0, ft_strlen(line) - ft_strlen(val));
	root = make_node_tr(key, val + 1, flag);
	free(key);
	return (root);
}

static t_tree_node	*make_bstree(char **mtx, int high, int low)
{
	t_tree_node	*root;
	int			mid;

	if (high < low)
		return (NULL);
	mid = low + (high - low) / 2;
	root = __init__root__(mtx[mid]);
	root->left = make_bstree(mtx, high, mid + 1);
	root->right = make_bstree(mtx, mid - 1, low);
	return (root);
}

static void	sort_matrix(char **mtx)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (mtx[++i])
	{
		j = -1;
		while (++j < i)
		{
			if (strcmp_tr(mtx[j], mtx[i]) < 0)
			{
				tmp = mtx[j];
				mtx[j] = mtx[i];
				mtx[i] = tmp;
			}
		}
	}
}

static int	size_of_matrix(char **mtx)
{
	int	i;

	i = -1;
	while (mtx[++i])
		;
	return (i);
}

t_bs_tree_ptr	matrix_to_tree_tr(char **mtx)
{
	t_bs_tree	*tree;

	tree = init_tr();
	sort_matrix(mtx);
	tree->size = size_of_matrix(mtx);
	tree->root = make_bstree(mtx, tree->size - 1, 0);
	return (tree);
}
