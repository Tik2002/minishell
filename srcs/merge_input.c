/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:53:23 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 13:00:53 by tigpetro         ###   ########.fr       */
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

static bool	__is_mergeable__(t_node *curr)
{
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
		if (ft_check_cmp(curr->val, curr->next->val))
			return (true);
		return (false);
	}
	return (!ft_check_cmp(curr->val, " ") && !ft_check_cmp(curr->next->val,
			" "));
}

void	ft_merge_input(t_list_ptr line)
{
	t_node	*next;
	t_node	*curr;

	if (empty_lt(line) || !line->head->next)
		return ;
	curr = line->head;
	while (curr->next)
	{
		next = curr->next;
		if (__is_mergeable__(curr))
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
	ft_insert_set(set, start);
}
