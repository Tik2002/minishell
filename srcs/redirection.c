/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:40:42 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 22:04:02 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	__check__(t_node **curr)
{
	if (!(*curr)->next || ft_check_cmp((*curr)->next->val, ""))
	{
		ft_err_msg(": No such file or directory");
		return (false);
	}
	return (true);
}

static bool	__redirect_in__(t_command *cmd, t_node **curr)
{
	int	fd;

	if (!__check__(curr))
		return (false);
	if (ft_check_cmp((*curr)->val, "<"))
	{
		if (!ft_open(&fd, (*curr)->next->val, O_RDONLY))
			return (false);
		close(cmd->descriptor->stdin);
		cmd->descriptor->stdin = fd;
		cmd->redirection |= redirect_in;
	}
	else
	{
		if (!ft_heredoc(&fd, (*curr)->next->val, cmd->minishell->export))
			return (false);
		close(cmd->descriptor->stdin);
		cmd->descriptor->stdin = fd;
		cmd->redirection |= redirect_in | redirect_heredoc;
	}
	return (true);
}

static bool	__redirect_out__(t_command *cmd, t_node **curr)
{
	int	fd;

	if (!__check__(curr))
		return (false);
	if (ft_check_cmp((*curr)->val, ">"))
	{
		if (!ft_open(&fd, (*curr)->next->val, O_WRONLY | O_CREAT | O_TRUNC))
			return (false);
		close(cmd->descriptor->stdout);
		cmd->descriptor->stdout = fd;
		cmd->redirection |= redirect_out;
	}
	else
	{
		if (!ft_open(&fd, (*curr)->next->val, O_WRONLY | O_CREAT | O_APPEND))
			return (false);
		close(cmd->descriptor->stdout);
		cmd->descriptor->stdout = fd;
		cmd->redirection |= redirect_out;
	}
	return (true);
}

static bool	__check_cmp__(t_command *cmd, t_list_ptr list, t_node **curr,
		t_node **tmp)
{
	if (ft_check_cmp((*curr)->val, "<") || ft_check_cmp((*curr)->val, "<<"))
	{
		if (!__redirect_in__(cmd, curr))
			return (false);
		*tmp = (*tmp)->next;
		remove_node_lt(list, (*curr)->next);
		remove_node_lt(list, *curr);
	}
	else if (ft_check_cmp((*curr)->val, ">") || ft_check_cmp((*curr)->val,
			">>"))
	{
		if (!__redirect_out__(cmd, curr))
			return (false);
		*tmp = (*tmp)->next;
		remove_node_lt(list, (*curr)->next);
		remove_node_lt(list, *curr);
	}
	return (true);
}

bool	ft_check_redirections(t_command *cmd, t_list_ptr list, t_node *check)
{
	t_node	*curr;
	t_node	*tmp;

	curr = list->head;
	while (curr && curr->next)
	{
		tmp = curr->next;
		if (!ft_find_set(cmd->minishell->set, check) && !__check_cmp__(cmd, list, &curr, &tmp))
		{
			if (curr->next && *curr->next->val)
			{
				ft_err_msg(NULL);
				ft_putstr_fd(curr->next->val, STDERR_FILENO);
				ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			}
			set_status_unsigned(1);
			return (false);
		}
		curr = tmp;
		while(!ft_check_cmp(curr->val, check->val))
			check = check->next;
	}
	set_status_unsigned(0);
	return (true);
}
