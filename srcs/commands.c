/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:07:33 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 21:23:23 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	__check_builtins__(char *name)
{
	return (ft_check_cmp(name, "history") || ft_check_cmp(name, "env")
		|| ft_check_cmp(name, "export") || ft_check_cmp(name, "echo")
		|| ft_check_cmp(name, "pwd") || ft_check_cmp(name, "cd")
		|| ft_check_cmp(name, "exit") || ft_check_cmp(name, "unset"));
}

static void	__access_error__(char *cmd)
{
	if (get_status() == 1)
		return ;
	ft_err_msg("");
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (__check_redir__(cmd))
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
}


static bool	__check_name__(t_command *cmd)
{
	if (!cmd->args.head)
		return (false);
	return (ft_check_cmp(cmd->args.head->val, ".__quoted_redirection__"));
}

static void	__eval_commands__(t_cmd_matrix *cmd_matrix, int *pips, int i,
		bool *flag)
{
	if (i < cmd_matrix->size - 1)
		dup2(pips[out], STDOUT_FILENO);
	if (cmd_matrix->cmds[i]->redirection & redirect_in)
		dup2(cmd_matrix->cmds[i]->descriptor->stdin, STDIN_FILENO);
	if (cmd_matrix->cmds[i]->redirection & redirect_out)
		dup2(cmd_matrix->cmds[i]->descriptor->stdout, STDOUT_FILENO);
	if (__check_name__(cmd_matrix->cmds[i]))
		__access_error__(cmd_matrix->cmds[i]->name);
	else if (!__check_redir__(cmd_matrix->cmds[i]->name))
	{
		if (__check_builtins__(cmd_matrix->cmds[i]->name))
			ft_execute_builtins(cmd_matrix, i);
		else
		{
			if (ft_check_access(cmd_matrix->cmds[i], flag))
				ft_execute(cmd_matrix, i, flag, pips);
			else
				__access_error__(cmd_matrix->cmds[i]->name);
		}
	}
	dup2(pips[in], STDIN_FILENO);
	dup2(cmd_matrix->minishell->descriptor->stdout, STDOUT_FILENO);
	close(pips[in]);
	close(pips[out]);
}

void	ft_eval_commands(t_cmd_matrix *cmd_matrix)
{
	int		i;
	int		pips[2];
	bool	flag;

	i = -1;
	while (++i < cmd_matrix->size && cmd_matrix->cmds[i]->name)
	{
		flag = false;
		if (pipe(pips) < 0)
			return (ft_err_msg("fork: Resource temporarily unavailable"));
		__eval_commands__(cmd_matrix, pips, i, &flag);
		if (cmd_matrix->cmds[i]->redirection & redirect_heredoc)
			unlink(".heredoc.txt");
		if (cmd_matrix->cmds[0]->pid == -1)
			return (set_status_unsigned(1));
	}
	while (-1 != wait(NULL))
		;
}
