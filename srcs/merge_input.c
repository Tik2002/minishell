/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:53:23 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 22:11:18 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	__check_cmp__(char *val)
{
	return (ft_check_cmp(val, ">") || ft_check_cmp(val, ">>")
		|| ft_check_cmp(val, "<") || ft_check_cmp(val, "<<")
		|| ft_check_cmp(val, "&&") || ft_check_cmp(val, "||")
		|| ft_check_cmp(val, "|") || ft_check_cmp(val, " "));
}

static bool	__is_mergeable__(t_node *curr, t_set *set)
{
	if (ft_find_set(set, curr) && ft_find_set(set, curr->next))
		return (true);
	if ((__check_cmp__(curr->val) && !__check_cmp__(curr->next->val))
		|| (__check_cmp__(curr->next->val) && !__check_cmp__(curr->val)))
		return (false);
	if (ft_check_cmp(curr->val, ")") || ft_check_cmp(curr->next->val, ")")
		|| ft_check_cmp(curr->next->val, "(") || ft_check_cmp(curr->val, "("))
		return (false);
	if (ft_check_cmp(curr->val, "||") || ft_check_cmp(curr->val, "&&")
		|| ft_check_cmp(curr->val, "<<") || ft_check_cmp(curr->val, ">>"))
		return (false);
	if (ft_check_cmp(curr->val, "<") || ft_check_cmp(curr->val, ">")
		|| ft_check_cmp(curr->val, "|") || ft_check_cmp(curr->val, "&"))
	{
		if (ft_check_cmp(curr->val, curr->next->val) && !ft_find_set(set, curr) && !ft_find_set(set, curr->next))
			return (true);
		return (false);
	}
	return (!ft_check_cmp(curr->val, " ") && !ft_check_cmp(curr->next->val,
			" "));
}

void	ft_merge_input(t_list_ptr line, t_set *set)
{
	t_node	*next;
	t_node	*curr;

	if (empty_lt(line) || !line->head->next)
		return ;
	curr = line->head;
	while (curr->next)
	{
		next = curr->next;
		if (__is_mergeable__(curr, set))
		{
			ft_append(&curr->val, next->val);
			remove_node_lt(line, next);
		}
		else
			curr = next;
	}
}

void	ft_merge_quotes(t_list_ptr line, t_node *start, t_node *end, t_set *set)
{
	if (start == end)
	{
		insert_node_lt(line, "", start);
	}
	else
	{
		while (start->next != end)
		{
			ft_append(&start->val, start->next->val);
			remove_node_lt(line, start->next);
		}
	}
	if (ft_check_cmp(end->val, "\'"))
		ft_insert_set(set, start, single_q);
	ft_insert_set(set, start, double_q);
}
