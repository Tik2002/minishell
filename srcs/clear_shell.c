/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:03:42 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 18:47:08 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_clear_minishell(t_minishell *minishell)
{
	clear_lt(&minishell->history);
	clear_tr(minishell->export);
	clear_lt(&minishell->line);
}

void	ft_clear_cmds(t_command **cmd)
{
	dup2((*cmd)->minishell->descriptor->stderr, STDERR_FILENO);
	dup2((*cmd)->minishell->descriptor->stdout, STDOUT_FILENO);
	dup2((*cmd)->minishell->descriptor->stdin, STDIN_FILENO);
	free((*cmd)->name);
	(*cmd)->name = NULL;
	clear_lt(&(*cmd)->args);
	clear_lt(&(*cmd)->opts);
	(*cmd)->minishell = NULL;
	close((*cmd)->descriptor->stderr);
	close((*cmd)->descriptor->stdin);
	close((*cmd)->descriptor->stdout);
	free((*cmd)->descriptor);
	(*cmd)->descriptor = NULL;
	free(*cmd);
	*cmd = NULL;
}

void	ft_clear_cmds_matrix(t_cmd_matrix **mtx)
{
	t_cmd_matrix	*tmp;
	int				i;

	i = -1;
	tmp = *mtx;
	while (++i < tmp->size)
		ft_clear_cmds(&tmp->cmds[i]);
	free(tmp->cmds);
	tmp->cmds = NULL;
	tmp->size = 0;
	tmp->minishell = NULL;
}

void	ft_clear_container(t_container **container)
{
	t_container	*tmp;
	int			i;

	tmp = *container;
	i = -1;
	while (++i < tmp->size)
	{
		ft_clear_cmds_matrix(&tmp->cmds_mtx[i]);
		free(tmp->cmds_mtx[i]);
		tmp->cmds_mtx[i] = NULL;
	}
	free(tmp->cmds_mtx);
	tmp->cmds_mtx = NULL;
	tmp->size = 0;
	clear_as_tr(tmp->as_tree);
	free(tmp->as_tree);
	tmp->as_tree = NULL;
	tmp->minishell = NULL;
	free(tmp);
	tmp = NULL;
}
