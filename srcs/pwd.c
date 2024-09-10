/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:08:12 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/10 16:16:05 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*__ft_pwd__(t_bs_tree_ptr export)
{
	char	*path;
	int		size;

	size = 4224;
	path = wrapper_malloc(size + 1);
	if (!getcwd(path, size))
	{
		free(path);
		path = ft_strdup(get_tr(export, "PWD"));
		ft_append(&path, "/../");
	}
	return (path);
}

void	ft_pwd(t_command *cmd)
{
	char	*path;
	int		status;

	status = 0;
	if (cmd->opts.head)
		status = 1;
	else
	{
		path = get_tr(cmd->minishell->export, "PWD");
		if (path && *path)
		{
			printf("%s\n", path);
			return ;
		}
		path = __ft_pwd__(cmd->minishell->export);
		printf("%s\n", path);
		free (path);
	}
	set_status_unsigned(status);
}
