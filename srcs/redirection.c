/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:40:42 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/09 16:24:57 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	__check__(t_node *curr)
{
	if (!curr->next || ft_check_cmp(curr->next->val, ""))
	{
		ft_err_msg(": No such file or directory");
		return (false);
	}
	return (true);
}

static bool	__redirect_in__(t_command *cmd, t_node *curr, t_node *check)
{
	int	fd;

	if (!__check__(curr))
		return (false);
	if (ft_check_cmp(curr->val, "<"))
	{
		if (!ft_open(&fd, curr->next->val, O_RDONLY))
			return (false);
		close(cmd->descriptor->stdin);
		cmd->descriptor->stdin = fd;
		cmd->redirection |= redirect_in;
	}
	else
	{
		if (!ft_heredoc(&fd, curr->next, cmd->minishell, check))
			return (false);
		close(cmd->descriptor->stdin);
		cmd->descriptor->stdin = fd;
		cmd->redirection |= redirect_in | redirect_heredoc;
	}
	return (true);
}

static bool	__redirect_out__(t_command *cmd, t_node *curr)
{
	int	fd;

	if (!__check__(curr))
		return (false);
	if (ft_check_cmp(curr->val, ">"))
	{
		if (!ft_open(&fd, curr->next->val, O_WRONLY | O_CREAT | O_TRUNC))
			return (false);
		close(cmd->descriptor->stdout);
		cmd->descriptor->stdout = fd;
		cmd->redirection |= redirect_out;
	}
	else
	{
		if (!ft_open(&fd, curr->next->val, O_WRONLY | O_CREAT | O_APPEND))
			return (false);
		close(cmd->descriptor->stdout);
		cmd->descriptor->stdout = fd;
		cmd->redirection |= redirect_out;
	}
	return (true);
}

static bool	__check_cmp__(t_command *cmd, t_list_ptr list, t_node *check,
		t_node **tmp)
{
	t_node	*curr;

	curr = (*tmp)->prev;
	if (ft_check_cmp(curr->val, "<") || ft_check_cmp(curr->val, "<<"))
	{
		if (!__redirect_in__(cmd, curr, check->next))
			return (false);
		*tmp = (*tmp)->next;
		remove_node_lt(list, curr->next);
		remove_node_lt(list, curr);
	}
	else if (ft_check_cmp(curr->val, ">") || ft_check_cmp(curr->val, ">>"))
	{
		if (!__redirect_out__(cmd, curr))
			return (false);
		*tmp = (*tmp)->next;
		remove_node_lt(list, curr->next);
		remove_node_lt(list, curr);
	}
	return (true);
}

bool	ft_check_redirections(t_command *cmd, t_list_ptr list, t_node *check)
{
	t_node	*curr;
	t_node	*tmp;

	curr = list->head;
	set_status_signed(0);
	while (curr && curr->next)
	{
		tmp = curr->next;
		if (!ft_find_set(cmd->minishell->set, check) && !__check_cmp__(cmd,
				list, check, &tmp))
		{
			if (curr->next && *curr->next->val)
			{
				__redir_util__(curr->next->val);
			}
			set_status_unsigned(1);
			return (false);
		}
		curr = tmp;
		if (!curr)
			break ;
		while (!ft_check_cmp(curr->val, check->val))
			check = check->next;
	}
	return (get_status() != 1);
}
