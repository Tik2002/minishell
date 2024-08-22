/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:34:54 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/12 22:31:33 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_execute_builtins(t_cmd_matrix *cmd_mtx, int i)
{
	if (ft_check_cmp(cmd_mtx->cmds[i]->name, "history"))
		ft_history(cmd_mtx->cmds[i]);
	if (ft_check_cmp(cmd_mtx->cmds[i]->name, "env"))
		ft_env(cmd_mtx->cmds[i]);
	if (ft_check_cmp(cmd_mtx->cmds[i]->name, "export"))
		ft_export(cmd_mtx->cmds[i], cmd_mtx->size);
	if (ft_check_cmp(cmd_mtx->cmds[i]->name, "echo"))
		ft_echo(cmd_mtx->cmds[i]);
	if (ft_check_cmp(cmd_mtx->cmds[i]->name, "pwd"))
		ft_pwd(cmd_mtx->cmds[i]);
	if (ft_check_cmp(cmd_mtx->cmds[i]->name, "cd"))
		ft_cd(cmd_mtx->cmds[i], cmd_mtx->size);
	if (ft_check_cmp(cmd_mtx->cmds[i]->name, "exit"))
		ft_exit(cmd_mtx, i);
	if (ft_check_cmp(cmd_mtx->cmds[i]->name, "unset"))
		ft_unset(cmd_mtx->cmds[i], cmd_mtx->size);
}
