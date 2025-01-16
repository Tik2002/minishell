/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:05:28 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:19:34 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#ifdef __linux__
# include <bits/sigaction.h>
# include <asm-generic/signal-defs.h>
#endif //__linux__

static void	__cleaner__(t_command *cmd, int fd, bool flag, int status)
{
	static int			_fd;
	static t_command	*_cmd;
	t_minishell			*minishell;

	if (!flag)
	{
		_cmd = cmd;
		_fd = fd;
	}
	else
	{
		minishell = _cmd->minishell;
		close(_fd);
		ft_clear_cmds(&_cmd);
		ft_clear_minishell(minishell);
		system("leaks minishell");
		exit (status);
	}
}

static void	signal_heredoc(int unused)
{
	(void)unused;
	__cleaner__(0, 0, true, 1);
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

static void	__heredoc__(char *delim, t_command *cmd, bool flag)
{
	char	*line;
	int		fd;

	set_signals_heredoc();
	ft_open(&fd, ".heredoc.txt", O_CREAT | O_RDWR);
	__cleaner__(cmd, fd, false, 0);
	while (true)
	{
		line = readline("here_doc> ");
		if (!line || ft_check_cmp(line, delim))
			break ;
		if (flag)
			ft_resolve_dollar(cmd->minishell->export, &line);
		ft_append(&line, "\n");
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	__cleaner__(0, 0, true, 0);
}

bool	ft_heredoc(int *fd, t_node *delim_node, t_command *cmd,
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
	flag = !ft_find_set(cmd->minishell->set, check);
	pid = fork();
	res = 0;
	if (pid == -1)
		ft_err_msg("here_doc fork error");
	if (pid == 0)
		__heredoc__(delim, cmd, flag);
	waitpid(pid, &res, 0);
	res = WEXITSTATUS(res);
	if (res == 1)
		set_status_signed(res);
	return (ft_open(fd, ".heredoc.txt", O_RDONLY));
}
