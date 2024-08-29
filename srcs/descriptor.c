/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descriptor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:16:15 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/29 14:35:59 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_descriptor	*make_descriptors(void)
{
	t_descriptor	*res;

	res = wrapper_malloc(sizeof(t_descriptor));
	res->stdout = dup(STDOUT_FILENO);
	res->stdin = dup(STDIN_FILENO);
	res->stderr = dup(STDERR_FILENO);
	return (res);
}

void	ft_reset_descriptors(t_command *cmd)
{
	if (!cmd || !cmd->minishell)
		return ;
	if (cmd->descriptor->stdin != cmd->minishell->descriptor->stdin)
	{
		close(cmd->descriptor->stdin);
		dup2(cmd->minishell->descriptor->stdin, STDIN_FILENO);
	}
	if (cmd->descriptor->stdout != cmd->minishell->descriptor->stdout)
	{
		close(cmd->descriptor->stdout);
		dup2(cmd->minishell->descriptor->stdout, STDOUT_FILENO);
	}
	if (cmd->descriptor->stderr != cmd->minishell->descriptor->stderr)
	{
		close(cmd->descriptor->stderr);
		dup2(cmd->minishell->descriptor->stderr, STDERR_FILENO);
	}
}
