/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:47:48 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 22:52:09 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_H
# define SET_H

# include "../includes/typedefs.h"
# include <libft.h>
# include <list.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_quoted		t_quoted;
typedef struct s_set		t_set;
typedef struct s_set_node	t_set_node;

struct						s_set_node
{
	t_node		*key;
	t_set_node	*next;
	t_quoted	quotes;
};

struct						s_set
{
	t_set_node	*head;
};

enum						e_quoted
{
	single_q,
	double_q,
};

// set
t_set	*ft_init_set(void);
bool	ft_empty_set(t_set *set);
void	ft_insert_set(t_set *set, t_node *node, t_quoted quote_t);
bool	ft_find_set(t_set *set, t_node *node);
void	ft_clear_set(t_set *set);

#endif // SET_H
