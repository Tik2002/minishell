/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_to_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:48:45 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 19:58:46 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bs_tree.h>

static void	get_string_tr(char **res, char *tmp, int *index)
{
	res[*index] = ft_strdup(tmp);
	(*index)++;
}

static void	__tree_to_matrix_tr__(t_tree_node *root, char **res, int *index)
{
	char	*tmp2;
	char	*tmp1;

	if (!root)
		return ;
	tmp1 = ft_strjoin(root->key, "=");
	tmp2 = ft_strjoin(tmp1, root->val);
	__tree_to_matrix_tr__(root->left, res, index);
	get_string_tr(res, tmp2, index);
	__tree_to_matrix_tr__(root->right, res, index);
	free(tmp1);
	free(tmp2);
}

char	**tree_to_matrix_tr(t_bs_tree_ptr tree)
{
	char	**res;
	int		i;

	i = 0;
	res = wrapper_malloc(sizeof(char *) * (tree->size + 1));
	printf("%d\n", tree->size);
	res[tree->size] = NULL;
	__tree_to_matrix_tr__(tree->root, res, &i);
	return (res);
}
