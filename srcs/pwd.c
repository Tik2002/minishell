/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:08:12 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 14:36:51 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*__ft_pwd__(void)
{
	char	*path;
	int		size;

	size = 4224;
	path = wrapper_malloc(size + 1);
	if (!getcwd(path, size))
		ft_append(&path, "/../");
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
		path = __ft_pwd__();
		printf("%s\n", path);
		free (path);
	}
	set_status_unsigned(status);
}
