/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:13:51 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:21:11 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	__exec_util__(char *name, char *err)
{
	ft_err_msg(NULL);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	set_status_unsigned(127);
}

void	__fork_error__(t_cmd_matrix *cmd_mtx, int index)
{
	while (--index >= 0)
	{
		if (cmd_mtx->cmds[index]->pid > -2)
			kill(cmd_mtx->cmds[index]->pid, SIGKILL);
		waitpid(cmd_mtx->cmds[index]->pid, NULL, 0);
		cmd_mtx->cmds[index]->pid = -1;
	}
	__exec_util__("fork", ": Resource temporarily unavailable");
}
