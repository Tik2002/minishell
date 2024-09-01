/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:37:39 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 22:42:00 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__push_back__(t_list_ptr list, t_node **curr)
{
	push_back_lt(list, (*curr)->val);
	*curr = (*curr)->next;
}

static void	__sort_input__(t_command *cmd, t_node **curr)
{
	while (*curr && (*curr)->val[0] == '-')
		__push_back__(&cmd->opts, curr);
	while (*curr)
		__push_back__(&cmd->args, curr);
}

static t_command	*__ft_init_command__(t_minishell *minishell,
		t_list_ptr list)
{
	t_command	*cmd;
	t_node		*curr;

	cmd = wrapper_malloc(sizeof(t_command));
	cmd->descriptor = make_descriptors();
	cmd->redirection = 0;
	cmd->minishell = minishell;
	cmd->pid = -2;
	init_lt(&cmd->args);
	init_lt(&cmd->opts);
	curr = list->head;
	cmd->name = ft_strdup(curr->val);
	if (!curr->next)
		return (cmd);
	if (!ft_check_redirections(cmd, list))
	{
		free(cmd->name);
		cmd->name = NULL;
		return (cmd);
	}
	curr = curr->next;
	__sort_input__(cmd, &curr);
	return (cmd);
}

static void	__init_command__(t_cmd_matrix *cmd_matrix, t_node *curr,
		t_node *end)
{
	t_list	list;
	t_node	*tail;
	int		i;

	i = -1;
	init_lt(&list);
	while (++i < cmd_matrix->size)
	{
		tail = find_word_range_lt(curr, end, "|", cmd_matrix->minishell->set);
		copy_range_lt(&list, curr, tail);
		cmd_matrix->cmds[i] = __ft_init_command__(cmd_matrix->minishell, &list);
		if (tail)
			curr = tail->next;
		clear_lt(&list);
	}
}

void	ft_init_command(t_container *container)
{
	int		i;
	t_node	*curr;
	t_node	*end;

	i = -1;
	curr = container->minishell->line.head;
	while (++i < container->size)
	{
		end = curr;
		while (end && !ft_find_set(container->minishell->set, end) && !ft_check_cmp(end->val, "||") && !ft_check_cmp(end->val,
				"&&"))
			end = end->next;
		__init_command__(container->cmds_mtx[i], curr, end);
		if (end)
			curr = end->next;
		else
			curr = end;
	}
}
