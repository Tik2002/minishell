/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:25:50 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:08:50 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	free_node(t_node **node)
{
	free((*node)->val);
	free(*node);
}

t_node	*make_node(char *str)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!str || !*str)
		node->val = ft_strdup("");
	else
		node->val = ft_strdup(str);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	print_lt(t_list_ptr list)
{
	t_node	*curr;

	curr = list->head;
	while (curr)
	{
		printf("%s\n", curr->val);
		curr = curr->next;
	}
}
