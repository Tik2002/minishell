/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:42:29 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/26 15:32:25 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(t_command *cmd)
{
	int		status;

	status = 0;
	if (!cmd->args.head && !cmd->opts.head)
	{
		update_tr(cmd->minishell->export, "_", "env", true);
		print_tr_custom(cmd->minishell->export, __print_env__);
		remove_tr(cmd->minishell->export, "_");
	}
	else if (cmd->opts.head)
	{
		ft_err_msg("env: no option required!!!");
		status = 1;
	}
	else
	{
		ft_err_msg("env: no argument required!!!");
		status = 127;
	}
	set_status_unsigned(status);
}
