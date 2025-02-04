/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:03:42 by tigpetro          #+#    #+#             */
/*   Updated: 2024/10/19 19:59:12 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_clear_minishell(t_minishell *minishell)
{
	if (minishell->container)
		ft_clear_container(&minishell->container);
	if (minishell->set)
	{
		ft_clear_set(minishell->set);
		free(minishell->set);
		minishell->set = NULL;
	}
	clear_lt(&minishell->history);
	clear_lt(&minishell->tmp);
	free(minishell->descriptor);
	clear_tr(minishell->export);
	free(minishell->export);
	clear_lt(&minishell->line);
}

void	ft_clear_cmds(t_command **cmd)
{
	ft_reset_descriptors(*cmd);
	free((*cmd)->descriptor);
	free((*cmd)->name);
	(*cmd)->name = NULL;
	(*cmd)->redirection = 0;
	(*cmd)->pid = 0;
	clear_lt(&(*cmd)->args);
	clear_lt(&(*cmd)->opts);
	(*cmd)->minishell = NULL;
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
	{
		if (tmp->cmds[i])
			ft_clear_cmds(&tmp->cmds[i]);
		free(tmp->cmds[i]);
		tmp->cmds[i] = NULL;
	}
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
		if (tmp->cmds_mtx[i])
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
	*container = NULL;
}
