/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimitors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:29:26 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/31 21:52:40 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__remove_set__(t_list_ptr line, t_set *set)
{
	t_set_node	*tmp;
	t_node		*curr;
	t_node		*next;

	tmp = set->head;
	curr = line->head;
	while (curr)
	{
		next = curr->next;
		if (tmp && curr == tmp->key)
			tmp = tmp->next;
		else if (ft_check_cmp(curr->val, " "))
			remove_node_lt(line, curr);
		curr = next;
	}
}

bool	ft_delim(t_bs_tree_ptr tree, t_list_ptr line, char *del, char *input)
{
	t_set	*set;

	ft_split_with_delim(line, del, input);
	if (!ft_quotes_and_bracket_checker(line))
	{
		ft_err_msg("quotes and brackets must be even");
		set_status_unsigned(50);
		return (false);
	}
	ft_handle_dollar_sign(line, tree);
	set = ft_init_set();
	ft_delete_quotes(line, set);
	ft_merge_input(line);
	__remove_set__(line, set);
	if (!ft_wildcards(line, set))
	{
		ft_err_msg("*: ambiguous redirect");
		ft_clear_set(&set);
		return (false);
	}
	ft_clear_set(&set);
	return (ft_check_syntax(line));
}
