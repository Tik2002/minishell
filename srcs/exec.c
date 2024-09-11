/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:09:44 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/10 19:07:43 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__util__(char *name, char *err)
{
	ft_err_msg(NULL);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	set_status_unsigned(127);
}

static void	ft_execute_proc(t_command *cmd)
{
	char	**cmd_mtx;
	char	**env;

	set_status_unsigned(0);
	push_front_lt(&cmd->opts, cmd->name);
	move_back_lt(&cmd->opts, &cmd->args);
	cmd_mtx = list_to_matrix_lt(&cmd->opts);
	env = tree_to_matrix_tr(cmd->minishell->export);
	execve(cmd_mtx[0], cmd_mtx, env);
	__util__(cmd_mtx[0], ": command not found");
	exit(127);
}

static void	__fork_error__(t_cmd_matrix *cmd_mtx, int index)
{
	while (--index >= 0)
	{
		if (cmd_mtx->cmds[index]->pid > -2)
			kill(cmd_mtx->cmds[index]->pid, SIGKILL);
		waitpid(cmd_mtx->cmds[index]->pid, NULL, 0);
		cmd_mtx->cmds[index]->pid = -1;
	}
	__util__("fork", ": Resource temporarily unavailable");
}

static void	__wait_for_childs__(t_command *cmd, int *status)
{
	waitpid(cmd->pid, status, 0);
	if (WIFSIGNALED(*status))
	{
		*status = WTERMSIG(*status) + 128;
		if (*status == 131)
			write(1, "Quit: 3\n", 9);
		return (set_status_unsigned(*status));
	}
	set_status_unsigned(WEXITSTATUS(*status));
}

void	ft_execute(t_cmd_matrix *cmd_mtx, int index, bool *flag, int *pips)
{
	int	status;

	if (!*flag || cmd_mtx->cmds[index]->name[0] == '.')
	{
		if (!*flag)
			__util__(cmd_mtx->cmds[index]->name, ": command not found");
		if (!*flag || !ft_check_script(cmd_mtx->cmds[index]->name))
			return ;
	}
	cmd_mtx->cmds[index]->pid = fork();
	if (cmd_mtx->cmds[index]->pid < 0)
		return (__fork_error__(cmd_mtx, index));
	if (cmd_mtx->cmds[index]->pid == 0)
	{
		close(pips[in]);
		ft_execute_proc(cmd_mtx->cmds[index]);
	}
	if (index == cmd_mtx->size - 1)
	{
		__wait_for_childs__(cmd_mtx->cmds[index], &status);
	}
}
