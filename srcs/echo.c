/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:31:07 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/29 19:10:37 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	__check__(char *val)
{
	int	i;

	i = -1;
	if (ft_check_cmp(val, "-n"))
		return (true);
	if (val[++i] == '-' && val[++i] == 'n')
	{
		while (val[++i])
		{
			if (val[i] != 'n')
				return (false);
		}
		return (true);
	}
	return (false);
}

void	ft_echo(t_command *cmd)
{
	t_node	*curr;
	bool	flag;

	flag = true;
	move_back_lt(&cmd->opts, &cmd->args);
	curr = cmd->opts.head;
	while (curr && __check__(curr->val))
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
