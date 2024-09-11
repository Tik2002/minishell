/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:37:39 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/10 19:07:51 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__sort_input__(t_command *cmd, t_list_ptr list, t_node **curr,
		t_node *check)
{
	if (ft_check_cmp((*curr)->next->val, "__ambiguous__")
		|| !ft_check_redirections(cmd, list, check))
	{
		free(cmd->name);
		cmd->name = NULL;
		return ;
	}
	*curr = (*curr)->next;
	while (*curr && (*curr)->val[0] == '-')
	{
		push_back_lt(&cmd->opts, (*curr)->val);
		*curr = (*curr)->next;
	}
	while (*curr)
	{
		push_back_lt(&cmd->args, (*curr)->val);
		*curr = (*curr)->next;
	}
}

static void	__cmd_name__(t_command *cmd, t_node *check)
{
	if (__check_redir__(cmd->name))
	{
		if (ft_find_set(cmd->minishell->set, check))
			push_front_lt(&cmd->args, ".__quoted_redirection__");
		else
			push_front_lt(&cmd->args, ".__redirection__");
	}
}

static t_command	*__ft_init_command__(t_minishell *minishell,
		t_list_ptr list, t_node *check)
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
	__cmd_name__(cmd, check);
	if (!curr->next)
		return (cmd);
	__sort_input__(cmd, list, &curr, check);
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
		cmd_matrix->cmds[i] = __ft_init_command__(cmd_matrix->minishell, &list,
				curr);
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
		while (end && ((!ft_check_cmp(end->val, "||") && !ft_check_cmp(end->val,
						"&&")) || ft_find_set(container->minishell->set, end)))
			end = end->next;
		__init_command__(container->cmds_mtx[i], curr, end);
		if (end)
			curr = end->next;
		else
			curr = end;
	}
}
