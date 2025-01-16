/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:25:43 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:08:50 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BS_TREE_H
# define BS_TREE_H

# include <libft.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_tree_node	t_tree_node;
typedef struct s_bs_tree	t_bs_tree;
typedef t_bs_tree			*t_bs_tree_ptr;
typedef void				(*t_decorator)(t_tree_node *);

struct						s_tree_node
{
	char					*val;
	t_tree_node				*right;
	t_tree_node				*left;
	char					*key;
	bool					equal_ma;
};

struct						s_bs_tree
{
	t_tree_node				*root;
	int						size;
};

// decorators
void			__print_env__(t_tree_node *root);
void			__print_exp__(t_tree_node *root);

// find_min
t_tree_node		*find_min_tr(t_bs_tree_ptr tree);
t_tree_node		*__find_min_tr__(t_tree_node *root);

// find_max
t_tree_node		*find_max_tr(t_bs_tree_ptr tree);
t_tree_node		*__find_max_tr__(t_tree_node *root);

// find
t_tree_node		*find_tr(t_bs_tree_ptr tree, char *key);

// get_value
char			*get_tr(t_bs_tree_ptr tree, char *key);

// helpers
int				strcmp_tr(char const *s1, char const *s2);
t_tree_node		*make_node_tr(char *key, char *val, bool flag);
bool			empty_tr(t_bs_tree_ptr tree);
void			delete_node_tr(t_tree_node **root);

// insertions
t_bs_tree		*init_tr(void);
void			update_tr(t_bs_tree_ptr tree, char *key, char *val, bool flag);

// matrix_to_tree
t_bs_tree		*matrix_to_tree_tr(char **mtx);

// print
void			print_tr(t_bs_tree_ptr tree);
void			print_tr_custom(t_bs_tree_ptr tree, t_decorator f);

// removing
void			remove_tr(t_bs_tree_ptr tree, char *key);
void			clear_tr(t_bs_tree_ptr tree);

// utils
void			swap_tr(t_tree_node *left, t_tree_node *right);

// tree_to_matrix
char			**tree_to_matrix_tr(t_bs_tree_ptr tree);

#endif // BS_TREE_H
