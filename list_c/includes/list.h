/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:25:43 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:08:50 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../includes/typedefs.h"
# include <libft.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_quoted		t_quoted;
typedef struct s_node		t_node;
typedef struct s_list		t_list;
typedef t_list				*t_list_ptr;
typedef struct s_set		t_set;
typedef struct s_set_node	t_set_node;

struct					s_node
{
	char				*val;
	t_node				*prev;
	t_node				*next;
};

struct					s_list
{
	t_node				*head;
	t_node				*tail;
	int					size;
};

enum					e_quoted
{
	single_q,
	double_q,
};

struct					s_set_node
{
	t_node		*key;
	t_set_node	*next;
	t_quoted	quotes;
};

struct					s_set
{
	t_set_node	*head;
};

// set
t_set	*ft_init_set(void);
bool	ft_empty_set(t_set *set);
void	ft_insert_set(t_set *set, t_node *node, t_quoted quote_t);
bool	ft_find_set(t_set *set, t_node *node);
void	ft_clear_set(t_set *set);
bool	is_single_quoted(t_set *set, t_node *node);

bool	empty_lt(t_list_ptr list);

void	init_lt(t_list_ptr list);

void	push_back_lt(t_list_ptr list, char *const str);

void	move_back_lt(t_list_ptr left, t_list_ptr right);

void	push_front_lt(t_list_ptr list, char *const str);

void	insert_node_lt(t_list_ptr list, char *str, t_node *node);

void	remove_if_lt(t_list_ptr list, char *val);

void	remove_index_node_lt(t_list_ptr list, int index);

void	remove_node_lt(t_list_ptr list, t_node *node);

void	remove_if_range_lt(t_list_ptr list, t_node *start,
			t_node *end, char *val);

void	pop_back_lt(t_list_ptr list);

void	pop_front_lt(t_list_ptr list);

void	clear_lt(t_list_ptr list);

char	*at_lt(t_list_ptr list, int index);

bool	diff_lt(char *word, char *to_cmp);

void	copy_lt(t_list_ptr to_copy, t_list_ptr other);

void	copy_range_lt(t_list_ptr this, t_node *node,
			t_node *end);

int		value_counter_lt(t_list_ptr list, char *src, t_set *set);

t_node	*find_word_lt(t_node *node, char *word);
void	free_node(t_node **node);
t_node	*find_word_range_lt(t_node *curr, t_node *end, char *word, t_set *set);
t_node	*find_word_if_lt(t_node *node, bool (*p)(char *));
int		find_index_lt(t_list_ptr list, t_node *to_find);

char	**list_to_matrix_lt(t_list_ptr list);

// helpers.c
void	print_lt(t_list_ptr list);
t_node	*make_node(char *str);

#endif // LIST_H
