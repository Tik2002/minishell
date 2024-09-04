/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimitors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:29:26 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 22:30:24 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__remove_set__(t_list_ptr line, t_set *set)
{
	t_node		*curr;
	t_node		*next;

	curr = line->head;
	while (curr)
	{
		next = curr->next;
		if (!ft_find_set(set, curr) && ft_check_cmp(curr->val, " "))
			remove_node_lt(line, curr);
		curr = next;
	}
}

bool	ft_delim(t_minishell *minishell, char *del, char *input)
{
	ft_split_with_delim(&minishell->line, del, input);
	if (!ft_quotes_and_bracket_checker(&minishell->line))
	{
		ft_err_msg("quotes and brackets must be even");
		set_status_unsigned(50);
		return (false);
	}
	ft_delete_quotes(&minishell->line, minishell->set);
	ft_merge_input(&minishell->line, minishell->set);
	__remove_set__(&minishell->line, minishell->set);
	ft_handle_dollar_sign(&minishell->line, minishell->export);
	ft_wildcards(&minishell->line, minishell->set);
	return (true);
}
