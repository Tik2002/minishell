/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:25:52 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/27 18:49:01 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			g_status;

static void	__ft_minishell__(t_minishell *minishell, char *input)
{
	t_container		*container;

	if (!ft_delim(minishell->export, &minishell->line, "<>| \'\"()&", input))
		ft_err_msg("quotes: quotes must be even!!!");
	else if (empty_lt(&minishell->line))
	{
		set_status_signed(0);
		return ;
	}
	else if (ft_check_syntax(&minishell->line))
	{
		container = ft_init_container(minishell);
		ft_init_command(container);
		ft_eval_container(container);
		ft_clear_container(&container);
	}
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
	ft_clear_minishell(minishell);
	free(input);
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	minishell;

	if (argc != 1 || argv[1])
		_err("The invalid amount of arguments");
	ft_init_minishell(&minishell, env);
	ft_minishell(&minishell);
	return (0);
}
