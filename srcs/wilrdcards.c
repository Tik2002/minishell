/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilrdcards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:59:04 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 13:14:53 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__util__(t_list_ptr tmp, char *val, bool (*fptr)(char *, char *))
{
	t_node	*curr;
	t_node	*next;

	curr = tmp->head;
	while (curr)
	{
		next = curr->next;
		if (!fptr(curr->val, val))
			remove_node_lt(tmp, curr);
		curr = next;
	}
}

static void	__resolve_with_chars__(t_list_ptr tmp, char *val)
{
	t_list	list;
	t_node	*start;
	int		count;

	bool (*fptr)(char *, char *);
	init_lt(&list);
	ft_split_with_delim(&list, "*", val);
	count = value_counter_lt(&list, "*");
	start = list.head;
	while (!empty_lt(tmp) && start)
	{
		if (!ft_check_cmp(start->val, "*"))
		{
			if (count > 0)
				fptr = ft_str_contains;
			else
				fptr = ft_str_ends_with;
			__util__(tmp, start->val, fptr);
		}
		else
			count--;
		start = start->next;
	}
	clear_lt(&list);
}

static void	__replace_wildcard__(t_list_ptr tmp, t_node *curr, t_list_ptr line)
{
	t_node	*node;

	node = tmp->tail;
	while (node)
	{
		insert_node_lt(line, node->val, curr);
		node = node->prev;
	}
	remove_node_lt(line, curr);
	clear_lt(tmp);
}

static void	__resolve_wildcards__(t_node *curr, t_list_ptr line)
{
	DIR				*d;
	struct dirent	*dir;
	t_list			tmp;

	d = opendir(".");
	if (!d)
	{
		ft_err_msg("opendir error!!!");
		return ;
	}
	init_lt(&tmp);
	dir = readdir(d);
	while (dir)
	{
		if (*dir->d_name != '.')
			push_back_lt(&tmp, dir->d_name);
		dir = readdir(d);
	}
	if (!empty_lt(&tmp) && !__check_wildcards__(curr->val))
		__resolve_with_chars__(&tmp, curr->val);
	if (!empty_lt(&tmp))
		__replace_wildcard__(&tmp, curr, line);
	closedir(d);
}

void	ft_wildcards(t_list_ptr line)
{
	t_node	*curr;
	t_node	*next;

	if (empty_lt(line))
		return ;
	curr = line->head;
	while (curr)
	{
		next = curr->next;
		if (ft_strchr(curr->val, '*'))
			__resolve_wildcards__(curr, line);
		curr = next;
	}
}
