/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:09:44 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 20:58:06 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_execute_proc(t_command *cmd)
{
	char	**cmd_mtx;
	char	**env;
	int		i;

	set_status_unsigned(0);
	push_front_lt(&cmd->opts, cmd->name);
	move_back_lt(&cmd->opts, &cmd->args);
	cmd_mtx = list_to_matrix_lt(&cmd->opts);
	env = tree_to_matrix_tr(cmd->minishell->export);
	printf("executed\n");
	i = -1;
	while(cmd_mtx[++i])
		printf("%s\n", cmd_mtx[i]);
	i = -1;
	while(env[++i])
		printf("%s\n", env[i]);
	printf("%d\n", execve(cmd_mtx[0], cmd_mtx, env));
	printf("%d\n", errno);
	// printf("not executed\n");
	exit(EXIT_FAILURE);
}

void	ft_execute(t_cmd_matrix *cmd_mtx, int index, bool *flag)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!*flag)
	{
		ft_err_msg(NULL);
		ft_putstr_fd(cmd_mtx->cmds[index]->name, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		set_status_unsigned(127);
		return ;
	}
	pid = fork();
	if (pid < 0)
		_err("ERROR!");
	if (pid == 0)
	{
		ft_execute_proc(cmd_mtx->cmds[index]);
		if (index == cmd_mtx->size - 1)
		{
			waitpid(pid, &status, 0);
			set_status_unsigned(WEXITSTATUS(status));
		}
	}
	wait(NULL);
}
