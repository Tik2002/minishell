/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 00:46:19 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 11:58:42 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__util__(char *val, t_list_ptr list, bool flag)
{
	t_list	tmp;
	t_node	*next;

	init_lt(&tmp);
	ft_split_with_delim(&tmp, "=", val);
	if (flag)
		next = tmp.head->next->next;
	else
		next = tmp.head->next;
	copy_range_lt(list, next, NULL);
	ft_merge_input(list);
	push_front_lt(list, tmp.head->val);
	clear_lt(&tmp);
}

static void	__export__(char *val, t_minishell *minishell, int *status, int size)
{
	t_list	list;
	bool	flag;

	if (!val || !*val || !__check_key__(val))
	{
		ft_err_msg("export: bad input");
		*status = 1;
		return ;
	}
	flag = ft_strchr(val, '=');
	init_lt(&list);
	__util__(val, &list, flag);
	if (size == 1)
	{
		if (flag)
			update_tr(minishell->export, list.head->val, list.tail->val, flag);
		else
			update_tr(minishell->export, list.head->val, "", flag);
	}
	clear_lt(&list);
}

void	ft_export(t_command *cmd, int size)
{
	t_node	*curr;
	int		status;

	status = 0;
	curr = cmd->args.head;
	if (!cmd->args.head && !cmd->opts.head)
		print_tr_custom(cmd->minishell->export, __print_exp__);
	else if (cmd->opts.head)
	{
		ft_err_msg("export: no option required!!!");
		status = 2;
	}
	else
	{
		while (curr)
		{
			__export__(curr->val, cmd->minishell, &status, size);
			curr = curr->next;
		}
	}
	set_status_unsigned(status);
}
