/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:03:38 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/31 21:50:38 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	__check_quotes_and_bracket_closing__(t_list_ptr line,
		t_list_ptr list)
{
	t_node	*curr;

	curr = line->head;
	while (curr)
	{
		if (empty_lt(list) && ft_check_cmp(curr->val, ")"))
			return (false);
		else if (list->head && (ft_check_cmp(list->head->val, curr->val)
				|| (ft_check_cmp(curr->val, ")")
					&& ft_check_cmp(list->head->val, "("))))
			pop_front_lt(list);
		else if (empty_lt(list) && ((ft_check_cmp(curr->val, "\'")
					|| ft_check_cmp(curr->val, "\"") || ft_check_cmp(curr->val,
						"("))))
			push_front_lt(list, curr->val);
		curr = curr->next;
	}
	return (empty_lt(list));
}

bool	ft_quotes_and_bracket_checker(t_list_ptr line)
{
	t_list	list;
	bool	flag;

	init_lt(&list);
	flag = __check_quotes_and_bracket_closing__(line, &list);
	clear_lt(&list);
	return (flag);
}

static bool	p(char *val)
{
	return (ft_check_cmp(val, "\'") || ft_check_cmp(val, "\""));
}

void	ft_delete_quotes(t_list_ptr line, t_set *set)
{
	t_node	*curr;
	t_node	*pair;

	curr = find_word_if_lt(line->head, p);
	while (curr)
	{
		pair = find_word_lt(curr->next, curr->val);
		ft_merge_quotes(line, curr->next, pair, set);
		remove_node_lt(line, curr);
		curr = find_word_if_lt(pair->next, p);
		remove_node_lt(line, pair);
	}
}
