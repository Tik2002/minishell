/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:31:07 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 11:58:42 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_command *cmd)
{
	t_node	*curr;
	bool	flag;

	flag = true;
	move_back_lt(&cmd->opts, &cmd->args);
	curr = cmd->opts.head;
	while (curr && ft_check_cmp(curr->val, "-n"))
		curr = curr->next;
	if (curr == cmd->opts.head)
		flag = false;
	while (curr)
	{
		printf("%s", curr->val);
		curr = curr->next;
		if (curr)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	set_status_unsigned(0);
}
