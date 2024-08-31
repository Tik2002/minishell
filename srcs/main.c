/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:25:52 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/31 22:22:41 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			g_status;

static void	__ft_minishell__(t_minishell *minishell, char *input)
{
	t_container		*container;

	if (!ft_delim(minishell->export, &minishell->line, "<>| \'\"()&", input))
		return ;
	if (empty_lt(&minishell->line))
		return (set_status_signed(0));
	container = ft_init_container(minishell);
	ft_init_command(container);
	ft_eval_container(container);
	ft_clear_container(&container);
	add_history(input);
	ft_add_history(&minishell->history, input);
}

static void	ft_minishell(t_minishell *minishell)
{
	char	*input;

	while (true)
	{
		set_signals_interactive();
		input = readline("Bigishell>$ ");
		set_signals_noninteractive();
		if (!input || !ft_strlen(input))
		{
			if (!input)
			{
				printf("exit\n");
				break ;
			}
			free(input);
			continue ;
		}
		__ft_minishell__(minishell, input);
		clear_lt(&minishell->line);
		free(input);
	}
	free(input);
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	minishell;

	if (argc != 1 || argv[1])
		_err("The invalid amount of arguments");
	ft_init_minishell(&minishell, env);
	ft_minishell(&minishell);
	ft_clear_minishell(&minishell);
	return (get_status());
}
