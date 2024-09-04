/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilrdcards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:59:04 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 19:27:44 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__resolve_with_chars__(t_list_ptr tmp, char *val)
{
	t_list	list;

	init_lt(&list);
	ft_split_with_delim(&list, "*", val);
	__resolve_with_chars_util__(tmp, &list);
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
		ft_err_msg("opendir error");
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

static bool	__check__(t_set *set, t_node *curr)
{
	return (!ft_find_set(set, curr) && __check_redir__(curr->val)
		&& !ft_check_cmp(curr->val, "<<"));
}

void	ft_wildcards(t_list_ptr line, t_set *set)
{
	t_node	*curr;
	t_node	*next;

	if (empty_lt(line))
		return ;
	curr = line->head;
	while (curr)
	{
		next = curr->next;
		if (!ft_find_set(set, curr) && ft_strchr(curr->val, '*'))
		{
			if (curr->prev && __check__(set, curr->prev))
			{
				ft_err_msg("*: ambiguous redirect");
				remove_node_lt(line, curr->prev);
				remove_node_lt(line, curr);
			}
			else if (curr->prev && !ft_check_cmp(curr->prev->val, "<<"))
				__resolve_wildcards__(curr, line);
		}
		curr = next;
	}
}
