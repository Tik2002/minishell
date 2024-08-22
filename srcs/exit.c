/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:13:50 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 18:29:50 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__pass__(char **str, int *sign, char *lim)
{
	while (**str == '\t' || **str == ' ' || **str == '\v'
		|| **str == '\n' || **str == '\f' || **str == '\r')
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign *= -1;
		(*str)++;
	}
	if (*sign == 1)
		*lim = '7';
	else
		*lim = '8';
}

static bool	__get_status__(char *str, int *status)
{
	long long	res;
	char		lim;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (false);
	__pass__(&str, &sign, &lim);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || res > 922337203685477580
			|| (res == 922337203685477580 && str[i] > lim))
			return (false);
		res = res * 10 + (str[i] - '0');
		++i;
	}
	*status = sign * res;
	return (true);
}

static void	__exit__(int status, char *msg, t_cmd_matrix *mtx)
{
	set_status_unsigned(status);
	if (*msg)
		ft_err_msg(msg);
	if (mtx->size > 1)
		return ;
	ft_clear_minishell(mtx->minishell);
	ft_clear_container(&mtx->container);
	system("leaks minishell");
	exit(get_status());
}

void	ft_exit(t_cmd_matrix *cmd_mtx, int i)
{
	int	status;

	move_back_lt(&cmd_mtx->cmds[i]->opts, &cmd_mtx->cmds[i]->args);
	status = 0;
	if (cmd_mtx->cmds[i]->opts.size >= 1)
	{
		if (__get_status__(cmd_mtx->cmds[i]->opts.head->val, &status))
		{
			if (cmd_mtx->cmds[i]->opts.size == 1)
				__exit__(status, "", cmd_mtx);
			else
			{
				ft_err_msg("exit: numeric argument required!!!");
				set_status_unsigned(1);
				return ;
			}
		}
		else
			__exit__(255, "exit: numeric argument required!!!", cmd_mtx);
	}
	__exit__(status, "", cmd_mtx);
}
