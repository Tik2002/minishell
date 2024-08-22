/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:05:28 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/21 15:32:45 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_heredoc(int *fd, char *delim, t_bs_tree_ptr export)
{
	char	*line;

	if (!delim)
		return (false);
	ft_open(fd, ".heredoc.txt", O_CREAT | O_RDWR);
	line = readline("here_doc> ");
	while (line && !ft_check_cmp(line, delim))
	{
		ft_resolve_dollar(export, &line);
		ft_append(&line, "\n");
		ft_putstr_fd(line, *fd);
		free(line);
		line = readline("here_doc> ");
	}
	free(line);
	close(*fd);
	if (!ft_open(fd, ".heredoc.txt", O_RDONLY))
		return (false);
	return (true);
}
