/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:09:15 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 22:42:23 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__util__(t_list_ptr tmp, char *val, bool *flag, bool (*fptr)(char *,
			char *))
{
	t_node		*curr;
	t_node		*next;
	static int	len;

	if (*flag)
	{
		len = 0;
		*flag = false;
	}
	curr = tmp->head;
	while (curr)
	{
		next = curr->next;
		if (len >= (int)ft_strlen(curr->val) || !fptr(curr->val + len, val))
			remove_node_lt(tmp, curr);
		curr = next;
	}
	len += (int)ft_strlen(val);
}

void	__resolve_with_chars_util__(t_list_ptr tmp, t_list_ptr list)
{
	int		count;
	bool	flag;
	t_node	*start;

	bool (*fptr)(char *, char *);
	count = value_counter_lt(list, "*", NULL);
	start = list->head;
	flag = true;
	while (!empty_lt(tmp) && start)
	{
		if (!ft_check_cmp(start->val, "*"))
		{
			if (count > 0)
				fptr = ft_str_contains;
			else
				fptr = ft_str_ends_with;
			__util__(tmp, start->val, &flag, fptr);
		}
		else
			count--;
		start = start->next;
	}
}

bool	__check_wildcards__(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '*')
		++i;
	return (str[i] == '\0');
}
