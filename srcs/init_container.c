/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:56:44 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/29 16:42:14 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__make_cmds_mtx__(t_container *container, t_list_ptr line)
{
	t_node	*curr;
	int		i;

	i = -1;
	curr = line->head;
	while (++i < container->size)
	{
		container->cmds_mtx[i] = wrapper_malloc(sizeof(t_cmd_matrix));
		container->cmds_mtx[i]->size = 1;
		while (curr && !ft_check_cmp(curr->val, "||")
			&& !ft_check_cmp(curr->val, "&&"))
		{
			if (ft_check_cmp(curr->val, "|"))
				container->cmds_mtx[i]->size++;
			curr = curr->next;
		}
		container->cmds_mtx[i]->cmds = wrapper_malloc(sizeof(t_command)
				* (container->cmds_mtx[i]->size + 1));
		container->cmds_mtx[i]->cmds[container->cmds_mtx[i]->size] = NULL;
		container->cmds_mtx[i]->minishell = container->minishell;
		container->cmds_mtx[i]->container = container;
		if (curr)
			curr = curr->next;
	}
}

static void	__util__(t_container *container, t_node **oper, int *pr, int i)
{
	int			last_pr;
	t_node_type	node_type;
	t_priority	priority;

	last_pr = *pr;
	while (!ft_check_cmp((*oper)->val, "||") && !ft_check_cmp((*oper)->val,
			"&&"))
	{
		if (ft_check_cmp((*oper)->val, "("))
			--(*pr);
		if (ft_check_cmp((*oper)->val, ")"))
			++(*pr);
		*oper = (*oper)->next;
	}
	if (ft_check_cmp((*oper)->val, "||"))
		node_type = OR;
	else
		node_type = AND;
	if (i == 1 || last_pr <= *pr)
		priority = ROOT;
	else
		priority = RIGHT;
	insert_node_as_tr(container->as_tree, NULL, node_type, priority);
	insert_node_as_tr(container->as_tree, container->cmds_mtx[i], COMMAND,
		RIGHT);
}

static void	__make_as_tree__(t_container *container)
{
	t_node	*oper;
	int		i;
	int		pr;

	i = 0;
	pr = 0;
	oper = container->minishell->line.head;
	container->as_tree = init_as_tr(container->cmds_mtx[0]);
	while (++i < container->size)
	{
		__util__(container, &oper, &pr, i);
		oper = oper->next;
	}
}

t_container	*ft_init_container(t_minishell *minishell)
{
	t_container	*container;

	container = wrapper_malloc(sizeof(t_container));
	container->size = value_counter_lt(&minishell->line, "||")
		+ value_counter_lt(&minishell->line, "&&") + 1;
	container->cmds_mtx = wrapper_malloc(sizeof(t_cmd_matrix) * (container->size
				+ 1));
	container->cmds_mtx[container->size] = NULL;
	container->minishell = minishell;
	__make_cmds_mtx__(container, &minishell->line);
	__make_as_tree__(container);
	remove_if_lt(&minishell->line, ")");
	remove_if_lt(&minishell->line, "(");
	return (container);
}
