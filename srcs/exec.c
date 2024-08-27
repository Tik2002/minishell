/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:09:44 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/27 18:47:31 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	exit(EXIT_FAILURE);
}

static void	__util__(char *name, char *err)
{
	ft_err_msg(NULL);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	set_status_unsigned(127);
}

static bool	__more_check__(char *script)
{
	set_status_unsigned(0);
	if (!access(script, F_OK | X_OK))
		return (true);
	if (access(script, F_OK))
		__util__(script, ": No such file or directory");
	else if (access(script, X_OK))
		__util__(script, ": Permission denied");
	set_status_unsigned(126);
	return (false);
}

static bool	__check_script__(char *script, t_bs_tree_ptr tree)
{
	if (ft_check_cmp(script, "."))
	{
		__util__(script, ": filename argument required");
		set_status_unsigned(2);
		return (false);
	}
	set_status_unsigned(126);
	if (chdir(script) == 0)
	{
		chdir(get_tr(tree, "PWD"));
		__util__(script, ": is a directory");
		return (false);
	}
	if (ft_check_cmp(script + ft_strlen(script) - 1, "/"))
	{
		__util__(script, ": Not a directory");
		return (false);
	}
	return (__more_check__(script));
}

void	ft_execute(t_cmd_matrix *cmd_mtx, int index, bool *flag)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!*flag || cmd_mtx->cmds[index]->name[0] == '.')
	{
		if (!*flag)
			__util__(cmd_mtx->cmds[index]->name, ": command not found");
		if (!*flag || !__check_script__(cmd_mtx->cmds[index]->name,
				cmd_mtx->minishell->export))
			return ;
	}
	pid = fork();
	if (pid < 0)
		_err("ERROR!");
	if (pid == 0)
	{
		ft_execute_proc(cmd_mtx->cmds[index]);
	}
	if (index == cmd_mtx->size - 1)
	{
		waitpid(pid, &status, 0);
		set_status_unsigned(WEXITSTATUS(status));
	}
}
