/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:53:34 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 16:02:12 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	__check_cmp__(char *val)
{
	return (ft_check_cmp(val, ">") || ft_check_cmp(val, ">>")
		|| ft_check_cmp(val, "<") || ft_check_cmp(val, "<<")
		|| ft_check_cmp(val, "&&") || ft_check_cmp(val, "||")
		|| ft_check_cmp(val, "|"));
}

static bool	__check__(t_list_ptr line)
{
	t_node	*curr;

	curr = line->head;
	while (curr->next)
	{
		if (__check_cmp__(curr->val) && __check_cmp__(curr->next->val))
		{
			ft_err_msg("");
			ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
			ft_putstr_fd(curr->next->val, STDERR_FILENO);
			ft_putendl_fd("'", STDERR_FILENO);
			return (false);
		}
		curr = curr->next;
	}
	return (true);
}

bool	ft_check_syntax(t_list_ptr line)
{
	set_status_signed(258);
	if (!__check__(line))
		return (false);
	if (__check_cmp__(line->head->val))
	{
		ft_err_msg("");
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(line->head->val, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (false);
	}
	if (__check_cmp__(line->tail->val))
	{
		ft_err_msg("syntax error: unexpected end of line!!!");
		return (false);
	}
	set_status_unsigned(0);
	return (true);
}
