/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:03:24 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/29 16:04:39 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__unset__(char *val, t_minishell *minishell, int *status, int size)
{
	if (!val || !*val || !__check_key__(val))
	{
		ft_err_msg("unset: bad input");
		*status = 1;
	}
	if (size == 1)
		remove_tr(minishell->export, val);
}

void	ft_unset(t_command *cmd, int size)
{
	t_node	*curr;
	int		status;

	status = 0;
	curr = cmd->args.head;
	if (cmd->opts.head)
	{
		ft_err_msg("unset: no option required");
		status = 2;
	}
	else
	{
		while (curr)
		{
			__unset__(curr->val, cmd->minishell, &status, size);
			curr = curr->next;
		}
	}
	set_status_unsigned(status);
}
