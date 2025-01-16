/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:09:44 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:20:37 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	________(char **mtx)
{
	int	i;

	i = 0;
	while (mtx && mtx[i])
		free(mtx[i++]);
	free(mtx);
}

static void	ft_execute_proc(t_command *cmd, t_minishell *minishell)
{
	char	**cmd_mtx;
	char	**env;

	set_status_unsigned(0);
	push_front_lt(&cmd->opts, cmd->name);
	move_back_lt(&cmd->opts, &cmd->args);
	cmd_mtx = list_to_matrix_lt(&cmd->opts);
	env = tree_to_matrix_tr(cmd->minishell->export);
	execve(cmd_mtx[0], cmd_mtx, env);
	__exec_util__(cmd_mtx[0], ": command not found");
	ft_clear_minishell(minishell);
	________(cmd_mtx);
	________(env);
	system("leaks minishell");
	exit(127);
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
			__exec_util__(cmd_mtx->cmds[index]->name, ": command not found");
		if (!*flag || !ft_check_script(cmd_mtx->cmds[index]->name))
			return ;
	}
	*flag = false;
	cmd_mtx->cmds[index]->pid = fork();
	if (cmd_mtx->cmds[index]->pid < 0)
		return (__fork_error__(cmd_mtx, index));
	if (cmd_mtx->cmds[index]->pid == 0)
	{
		close(pips[in]);
		ft_execute_proc(cmd_mtx->cmds[index], cmd_mtx->minishell);
	}
	if (index == cmd_mtx->size - 1)
	{
		__wait_for_childs__(cmd_mtx->cmds[index], &status);
	}
}
