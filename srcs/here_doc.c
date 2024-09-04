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

static void	signal_heredoc(int unused)
{
	(void)unused;
	printf("\n");
	exit (130);
}

static void	set_signals_heredoc(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_heredoc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	disable_echoctl();
}

bool	ft_heredoc(int *fd, t_node *delim_node, t_minishell *minishell, t_node *check)
{
	char	*line;
	char	*delim;
	bool	flag;

	if (!delim_node->val)
		return (false);
	delim = delim_node->val;
	flag = ft_find_set(minishell->set, check->next);
	ft_open(fd, ".heredoc.txt", O_CREAT | O_RDWR);
	while (true)
	{
		line = readline("here_doc> ");
		set_signals_heredoc();
		if (!line || ft_check_cmp(line, delim))
			break ;
		if (flag)
			ft_resolve_dollar(minishell->export, &line);
		ft_append(&line, "\n");
		ft_putstr_fd(line, *fd);
		free(line);
	}
	free(line);
	close(*fd);
	return (ft_open(fd, ".heredoc.txt", O_RDONLY));
}
