/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:04:59 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/29 16:04:39 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_add_history(t_list_ptr history, char *input)
{
	push_back_lt(history, input);
}

void	ft_print_history(t_list_ptr history)
{
	int		i;
	t_node	*tmp;

	i = -1;
	tmp = history->head;
	while (++i < history->size)
	{
		printf("%d	", i + 1);
		printf("%s\n", tmp->val);
		tmp = tmp->next;
	}
	set_status_unsigned(0);
}

void	ft_history(t_command *cmd)
{
	if (!cmd->minishell->history.head)
		return ;
	else if (cmd->opts.head)
	{
		set_status_unsigned(2);
		ft_err_msg("history: no options required");
	}
	else if (cmd->args.head)
	{
		set_status_unsigned(1);
		ft_err_msg("history: no argument required");
	}
	else
		ft_print_history(&cmd->minishell->history);
}
