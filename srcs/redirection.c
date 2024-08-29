/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:40:42 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/29 16:04:39 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	__check__(t_node **curr)
{
	if (!(*curr) || !(*curr)->next || ft_check_cmp((*curr)->next->val, ""))
	{
		ft_err_msg("ambiguous redirect");
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
		{
			return (false);
		}
		cmd->descriptor->stdin = fd;
		cmd->redirection |= redirect_in;
	}
	else
	{
		if (!ft_heredoc(&fd, (*curr)->next->val, cmd->minishell->export))
		{
			return (false);
		}
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
		{
			return (false);
		}
		cmd->descriptor->stdout = fd;
		cmd->redirection |= redirect_out;
	}
	else
	{
		if (!ft_open(&fd, (*curr)->next->val, O_WRONLY | O_CREAT | O_APPEND))
		{
			return (false);
		}
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

bool	ft_check_redirections(t_command *cmd, t_list_ptr list)
{
	t_node	*tmp;
	t_node	*curr;

	curr = list->head;
	while (curr && curr->next)
	{
		tmp = curr->next;
		if (!__check_cmp__(cmd, list, &curr, &tmp))
		{
			set_status_unsigned(1);
			return (false);
		}
		curr = tmp;
	}
	set_status_unsigned(0);
	return (true);
}
