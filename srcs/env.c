/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:42:29 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 11:58:42 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(t_command *cmd)
{
	int		status;

	status = 0;
	if (!cmd->args.head && !cmd->opts.head)
		print_tr_custom(cmd->minishell->export, __print_env__);
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

char	**ft_get_path(char *path)
{
	char	**path_mtx;

	if (!path)
		return (NULL);
	path_mtx = ft_split(path, ':');
	return (path_mtx);
}
