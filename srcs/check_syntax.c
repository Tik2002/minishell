/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:53:34 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 22:32:52 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	__check_redir__(char *val)
{
	return (ft_check_cmp(val, ">") || ft_check_cmp(val, ">>")
		|| ft_check_cmp(val, "<") || ft_check_cmp(val, "<<"));
}

static bool	__check_cmp__(char *val)
{
	return (ft_check_cmp(val, "&&") || ft_check_cmp(val, "||")
		|| ft_check_cmp(val, "|"));
}

static bool	__check__(t_list_ptr line, t_set *set)
{
	t_node	*curr;

	curr = line->head;
	while (curr->next)
	{
		if ((!ft_find_set(set, curr) || !ft_find_set(set, curr->next))
			&& ((__check_redir__(curr->val) && __check_redir__(curr->next->val))
			|| (__check_redir__(curr->val) && __check_cmp__(curr->next->val))
			|| (__check_cmp__(curr->val) && __check_cmp__(curr->next->val))))
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

bool	ft_check_syntax(t_list_ptr line, t_set *set)
{
	if (empty_lt(line))
		return (true);
	set_status_signed(258);
	if (!__check__(line, set))
		return (false);
	if ((__check_cmp__(line->tail->val) || __check_redir__(line->tail->val)) && !ft_find_set(set, line->tail))
	{
		ft_err_msg("syntax error: unexpected end of line");
		return (false);
	}
	set_status_unsigned(0);
	return (true);
}
