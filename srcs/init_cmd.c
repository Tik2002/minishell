/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:37:39 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/16 19:37:18 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__sort_input__(t_command *cmd, t_node *check)
{
	t_node	*curr;

	if (ft_check_cmp(cmd->minishell->tmp.head->next->val, "__ambiguous__")
		|| !ft_check_redirections(cmd, &cmd->minishell->tmp, check))
	{
		free(cmd->name);
		cmd->name = NULL;
		return ;
	}
	if (!cmd->minishell->tmp.head || !cmd->minishell->tmp.head->next)
		return ;
	curr = cmd->minishell->tmp.head->next;
	while (curr && curr->val[0] == '-')
	{
		push_back_lt(&cmd->opts, curr->val);
		curr = curr->next;
	}
	while (curr)
	{
		push_back_lt(&cmd->args, curr->val);
		curr = curr->next;
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

static t_command	*__ft_init_command__(t_minishell *minishell, t_node *check)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->descriptor = make_descriptors();
	cmd->redirection = 0;
	cmd->minishell = minishell;
	cmd->pid = -2;
	init_lt(&cmd->args);
	init_lt(&cmd->opts);
	cmd->name = ft_strdup(minishell->tmp.head->val);
	__cmd_name__(cmd, check);
	if (!minishell->tmp.head->next)
		return (cmd);
	__sort_input__(cmd, check);
	return (cmd);
}

static void	__init_command__(t_cmd_matrix *cmd_matrix, t_node *curr,
		t_node *end)
{
	t_node	*tail;
	int		i;

	i = -1;
	init_lt(&cmd_matrix->minishell->tmp);
	while (++i < cmd_matrix->size)
	{
		tail = find_word_range_lt(curr, end, "|", cmd_matrix->minishell->set);
		copy_range_lt(&cmd_matrix->minishell->tmp, curr, tail);
		cmd_matrix->cmds[i] = __ft_init_command__(cmd_matrix->minishell, curr);
		if (tail)
			curr = tail->next;
		clear_lt(&cmd_matrix->minishell->tmp);
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
