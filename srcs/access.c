/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:59:27 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 15:47:22 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*path_for_exec(char *current_cmd, char **path)
{
	char	*tmp;
	char	*cmd;
	int		i;

	i = -1;
	cmd = ft_strdup(current_cmd);
	if (!access(cmd, X_OK | F_OK))
		return (cmd);
	while (path[++i])
	{
		free(cmd);
		tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(tmp, current_cmd);
		free(tmp);
		if (!access(cmd, X_OK | F_OK))
			return (cmd);
	}
	free(cmd);
	return (NULL);
}

bool	ft_check_access(t_command *cmd, bool *flag)
{
	char	*tmp;
	char	**path_mtx;
	int		i;

	if (!cmd->name)
		return (false);
	if (!*cmd->name)
		return (true);
	path_mtx = ft_get_path(get_tr(cmd->minishell->export, "PATH"));
	if (!path_mtx)
		return (false);
	tmp = path_for_exec(cmd->name, path_mtx);
	if (tmp)
	{
		*flag = true;
		free(cmd->name);
		cmd->name = tmp;
	}
	i = -1;
	while (path_mtx[++i])
		free(path_mtx[i]);
	free(path_mtx);
	return (true);
}
