/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:01:03 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 21:01:18 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

static t_set_node	*__make_set_node__(t_node *node, t_quoted quote_t)
{
	t_set_node	*set_node;

	set_node = wrapper_malloc(sizeof(t_set_node));
	set_node->key = node;
	set_node->next = NULL;
	set_node->quotes = quote_t;
	return (set_node);
}

t_set	*ft_init_set(void)
{
	t_set	*set;

	set = wrapper_malloc(sizeof(t_set));
	set->head = NULL;
	return (set);
}

bool	ft_empty_set(t_set *set)
{
	return (!set || !set->head);
}

void	ft_insert_set(t_set *set, t_node *node, t_quoted quote_t)
{
	t_set_node	*curr;

	if (ft_empty_set(set))
		set->head = __make_set_node__(node, quote_t);
	else
	{
		curr = set->head;
		while (curr->next)
			curr = curr->next;
		curr->next = __make_set_node__(node, quote_t);
	}
}

void	ft_clear_set(t_set *set)
{
	t_set_node	*curr;
	t_set_node	*next;

	if (ft_empty_set(set))
		return ;
	curr = set->head;
	while (curr)
	{
		next = curr->next;
		curr->next = NULL;
		curr->key = NULL;
		free(curr);
		curr = next;
	}
	set->head = NULL;
}
