/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:25:55 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/31 13:27:25 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <bs_tree.h>
# include <as_tree.h>
# include <typedefs.h>
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <list.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

enum						e_direct
{
	in = 0,
	out = 1,
	redirect_in = 2,
	redirect_out = 4,
	redirect_heredoc = 8
};

struct						s_set_node
{
	t_node		*key;
	t_set_node	*next;
};

struct						s_set
{
	t_set_node	*head;
};

struct						s_descriptor
{
	int						stdout;
	int						stdin;
	int						stderr;
};

struct						s_minishell
{
	t_list					line;
	t_list					history;
	t_bs_tree_ptr			export;
	t_descriptor			*descriptor;
};

struct						s_command
{
	t_minishell				*minishell;
	char					*name;
	t_list					args;
	t_list					opts;
	int						redirection;
	t_descriptor			*descriptor;
	pid_t					pid;
};

struct						s_cmd_matrix
{
	t_command				**cmds;
	t_container				*container;
	t_minishell				*minishell;
	int						size;
};

struct						s_container
{
	t_cmd_matrix			**cmds_mtx;
	t_as_tree_ptr			as_tree;
	t_minishell				*minishell;
	int						size;
};

// init
void			ft_init_minishell(t_minishell *minishell, char **env);
void			ft_init_command(t_container *container);
t_container		*ft_init_container(t_minishell *minishell);

// signals_utils
void			disable_echoctl(void);
void			signal_print_newline(int signal);
void			ignore_sigquit(void);
void			signal_reset_prompt(int sig);

// signals_interactive
void			set_signals_interactive(void);

// signals_noninteractive
void			set_signals_noninteractive(void);

// check_delimitors
bool			ft_delim(t_bs_tree_ptr tree, t_list_ptr line, char *del,
					char *input);

// split_with_delimitors
void			ft_split_with_delim(t_list_ptr line, char *del, char *input);

// handle_dollar_sign
void			ft_resolve_dollar(t_bs_tree_ptr tree, char **val);
void			ft_handle_dollar_sign(t_list_ptr line, t_bs_tree_ptr tree);

// quotes
bool			ft_quotes_and_bracket_checker(t_list_ptr line);
void			ft_delete_quotes(t_list_ptr line, t_set *set);

// set
t_set			*ft_init_set(void);
bool			ft_empty_set(t_set *set);
void			ft_insert_set(t_set *set, t_node *node);
void			ft_clear_set(t_set **set);

// merge_input
void			ft_merge_quotes(t_list_ptr line, t_node *start, t_node *end,
					t_set *set);
void			ft_merge_input(t_list_ptr line);

// wildcards
void			ft_wildcards(t_list_ptr line);
bool			__check_wildcards__(char *str);
void			__resolve_with_chars_util__(t_list_ptr tmp, t_list_ptr list);

// utils
void			ft_split_to_list(t_list_ptr list, char del, char *input);
void			ft_err_msg(char *msg);

// append
void			ft_append(char **left, char *right);

// eval
void			ft_eval_container(t_container *container);

// check_script
bool			ft_check_script(char *script, t_bs_tree_ptr tree);

// commands
void			ft_eval_commands(t_cmd_matrix *cmd_matrix);
bool			ft_check_cmp(char *s1, char *s2);

// descriptor
t_descriptor	*make_descriptors(void);
void			ft_reset_descriptors(t_command *cmd);

// redirection
bool			ft_check_redirections(t_command *cmd, t_list_ptr list);

// clear
void			ft_clear_cmds(t_command **cmd);
void			ft_clear_cmds_matrix(t_cmd_matrix **mtx);
void			ft_clear_minishell(t_minishell *minishell);
void			ft_clear_container(t_container **container);

// builtins
void			ft_execute_builtins(t_cmd_matrix *cmd_mtx, int i);

// env
void			ft_env(t_command *cmd);
char			**ft_get_path(char *path);

// export
void			ft_export(t_command *cmd, int size);

// unset
void			ft_unset(t_command *cmd, int size);

// key_utils
bool			__check_key__(char *val);
bool			__is_valid_key__(char c);
int				__strlen_till__(char *str);
int				__counter__(char *str, char c);
int				__strlen_till_dollar__(char *str);

// check_syntax
bool			ft_check_syntax(t_list_ptr line);

// history
void			ft_add_history(t_list_ptr history, char *input);
void			ft_print_history(t_list_ptr history);
void			ft_history(t_command *cmd);

// access
bool			ft_check_access(t_command *cmd, bool *flag);

// open
bool			ft_open(int *fd, char *filename, int option);

// here_doc
bool			ft_heredoc(int *fd, char *delim, t_bs_tree_ptr export);

// exec
void			ft_execute(t_cmd_matrix *cmd_mtx, int index, bool *flag,
					int *pips);

// echo
void			ft_echo(t_command *cmd);

// pwd
char			*__ft_pwd__(void);
void			ft_pwd(t_command *cmd);

// cd
void			ft_cd(t_command *cmd, int size);

// exit
void			ft_exit(t_cmd_matrix *cmd_mtx, int i);

// status
void			set_status_unsigned(int status);
void			set_status_signed(int status);
int				get_status(void);

#endif // MINISHELL_H
