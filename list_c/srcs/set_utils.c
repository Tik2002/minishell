/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:29:57 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/09 21:31:33 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

bool	ft_find_set(t_set *set, t_node *node)
{
	t_set_node	*curr;

	if (ft_empty_set(set))
		return (false);
	curr = set->head;
	while (curr)
	{
		if (curr->key == node)
			return (true);
		curr = curr->next;
	}
	return (false);
}

bool	is_single_quoted(t_set *set, t_node *node)
{
	t_set_node	*curr;

	if (ft_empty_set(set))
		return (false);
	curr = set->head;
	while (curr)
	{
		if (curr->key == node && curr->quotes == single_q)
			return (true);
		curr = curr->next;
	}
	return (false);
}
