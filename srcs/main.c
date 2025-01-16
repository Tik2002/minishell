/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:25:52 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:21:51 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			g_status;

static void	__clear__set__(t_minishell *minishell)
{
	ft_clear_set(minishell->set);
	free(minishell->set);
	minishell->set = NULL;
}

static void	__ft_minishell__(t_minishell *minishell, char *input)
{
	minishell->set = ft_init_set();
	if (!ft_delim(minishell, "<>| \'\"()&", input))
		return (__clear__set__(minishell));
	add_history(input);
	ft_add_history(&minishell->history, input);
	if (!ft_check_syntax(&minishell->line, minishell->set)
		|| empty_lt(&minishell->line))
		return (__clear__set__(minishell), set_status_unsigned(get_status()));
	minishell->container = ft_init_container(minishell);
	ft_init_command(minishell->container);
	ft_eval_container(minishell->container);
	ft_clear_container(&minishell->container);
	__clear__set__(minishell);
}

static void	ft_minishell(t_minishell *minishell)
{
	char	*input;

	while (true)
	{
		set_signals_interactive();
		input = readline("Vermishell>$ ");
		set_signals_noninteractive();
		if (!input || !ft_strlen(input))
		{
			if (!input)
			{
				write(2, "exit\n", 5);
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
		_err("Minishell: invalid amount of arguments");
	ft_init_minishell(&minishell, env);
	ft_minishell(&minishell);
	ft_clear_minishell(&minishell);
	system("leaks minishell");
	return (get_status());
}
