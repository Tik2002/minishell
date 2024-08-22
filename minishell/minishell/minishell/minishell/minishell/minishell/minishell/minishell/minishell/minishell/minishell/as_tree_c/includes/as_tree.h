/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:25:43 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/21 17:36:52 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AS_TREE_H
# define AS_TREE_H

# include "../includes/typedefs.h"
# include <libft.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_as_tree_node	t_as_tree_node;
typedef struct s_as_tree		t_as_tree;
typedef t_as_tree				*t_as_tree_ptr;
typedef enum e_node_type		t_node_type;
typedef enum e_priority			t_priority;

enum							e_node_type
{
	OR,
	AND,
	COMMAND,
};

enum							e_priority
{
	ROOT,
	RIGHT,
};

struct							s_as_tree_node
{
	t_node_type					node_type;
	t_cmd_matrix				*cmd_mtx;
	t_as_tree_node				*right;
	t_as_tree_node				*left;
};

struct							s_as_tree
{
	t_as_tree_node				*root;
};

// decorators

// find_min

// find_max

// find

// get_value

// clear
void			clear_as_tr(t_as_tree_ptr tree);

// make
t_as_tree_ptr	init_as_tr(t_cmd_matrix *cmd_mtx);
t_as_tree_node	*make_as_node_tr(t_as_tree_node *node, t_cmd_matrix *cmd_mtx,
					t_node_type node_type);

// insertions
void			insert_node_as_tr(t_as_tree_ptr	tree, t_cmd_matrix *cmd_mtx,
					t_node_type type, t_priority priority);

// matrix_to_tree

// print
void			print_as_tr(t_as_tree_ptr tree);

// removing

// utils

// tree_to_matrix

#endif // AS_TREE_H
