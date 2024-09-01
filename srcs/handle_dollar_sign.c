/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:35:42 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 22:02:33 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__get_val__(char **val, t_bs_tree_ptr tree)
{
	char	*new_val;

	new_val = get_tr(tree, *val);
	if (ft_check_cmp(*val, "?"))
	{
		free(*val);
		*val = ft_itoa(get_status());
		return ;
	}
	free(*val);
	if (!new_val)
		*val = ft_strdup("");
	else
		*val = ft_strdup(new_val);
}

static void	__get_path__(char **val, t_bs_tree_ptr tree)
{
	char	*right;
	char	*left;
	int		left_size;
	int		right_size;
	int		i;

	i = -1;
	left_size = __strlen_till__(*val);
	left = wrapper_malloc(left_size + 1);
	left[left_size] = '\0';
	while (++i < left_size)
		left[i] = *(*val + i);
	__get_val__(&left, tree);
	right_size = ft_strlen(*val) - left_size;
	right = wrapper_malloc(right_size + 1);
	right[right_size] = '\0';
	i = -1;
	while (++i < right_size)
		right[i] = *(*val + i + left_size);
	free(*val);
	*val = ft_strjoin(left, right);
	free(left);
	free(right);
}

static void	__proc__(char **val, t_bs_tree_ptr tree)
{
	t_list	list;
	t_node	*curr;

	init_lt(&list);
	ft_split_with_delim(&list, "$", *val);
	curr = list.head;
	while (curr && curr->next)
	{
		if (ft_check_cmp(curr->val, "$"))
		{
			if (!ft_check_cmp(curr->val, curr->next->val))
			{
				__get_path__(&curr->next->val, tree);
				curr = curr->next;
				remove_node_lt(&list, curr->prev);
			}
			else
				curr = curr->next;
		}
		curr = curr->next;
	}
	ft_merge_input(&list, NULL);
	free(*val);
	*val = ft_strdup(list.head->val);
	clear_lt(&list);
}

void	ft_resolve_dollar(t_bs_tree_ptr tree, char **val)
{
	if (!__counter__(*val, '$') || ft_strlen(*val) == 1)
		return ;
	__proc__(val, tree);
}

void	ft_handle_dollar_sign(t_list_ptr line, t_bs_tree_ptr tree)
{
	t_node	*curr;
	t_list	stack;

	if (empty_lt(line))
		return ;
	init_lt(&stack);
	curr = line->head;
	while (curr)
	{
		if (ft_check_cmp(curr->val, "\'") || ft_check_cmp(curr->val, "\""))
		{
			if (!empty_lt(&stack) && ft_check_cmp(curr->val, stack.head->val))
				pop_front_lt(&stack);
			else if (empty_lt(&stack))
				push_front_lt(&stack, curr->val);
		}
		if (empty_lt(&stack) || ft_check_cmp(stack.head->val, "\""))
			if (ft_strchr(curr->val, '$'))
			{
				ft_resolve_dollar(tree, &curr->val);
				if (!*curr->val)
					remove_node_lt(line, curr);
			}
		curr = curr->next;
	}
}
