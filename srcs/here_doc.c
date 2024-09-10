/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:05:28 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/10 17:45:22 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	signal_heredoc(int unused)
{
	(void)unused;
	exit(1);
}

static void	set_signals_heredoc(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_heredoc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	disable_echoctl();
}

static int	__heredoc__(char *delim, t_minishell *minishell, bool flag)
{
	char	*line;
	int		fd;

	ft_open(&fd, ".heredoc.txt", O_CREAT | O_RDWR);
	set_signals_heredoc();
	while (true)
	{
		line = readline("here_doc> ");
		if (!line || ft_check_cmp(line, delim))
			break ;
		if (flag)
			ft_resolve_dollar(minishell->export, &line);
		ft_append(&line, "\n");
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

bool	ft_heredoc(int *fd, t_node *delim_node, t_minishell *minishell,
		t_node *check)
{
	pid_t	pid;
	int		res;
	bool	flag;
	char	*delim;

	ignore_sigquit();
	if (!delim_node->val)
		return (false);
	delim = delim_node->val;
	flag = !ft_find_set(minishell->set, check);
	pid = fork();
	res = 0;
	if (pid == -1)
		ft_err_msg("here_doc fork error");
	if (pid == 0)
		__heredoc__(delim, minishell, flag);
	waitpid(pid, &res, 0);
	res = WEXITSTATUS(res);
	if (res == 1)
		set_status_signed(res);
	return (ft_open(fd, ".heredoc.txt", O_RDONLY));
}
