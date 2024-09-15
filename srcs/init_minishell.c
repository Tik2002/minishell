/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:38:20 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/15 16:58:33 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_init_minishell(t_minishell *minishell, char **env)
{
	char	*shlvl;
	char	*pwd;

	init_lt(&(minishell->line));
	init_lt(&(minishell->history));
	minishell->export = matrix_to_tree_tr(env);
	minishell->set = NULL;
	minishell->container = NULL;
	minishell->descriptor = make_descriptors();
	update_tr(minishell->export, "OLDPWD", "", false);
	pwd = __ft_pwd__(minishell->export);
	update_tr(minishell->export, "PWD", pwd, true);
	remove_tr(minishell->export, "_");
	shlvl = ft_itoa(ft_atoi(get_tr(minishell->export, "SHLVL")) + 1);
	update_tr(minishell->export, "SHLVL", shlvl, true);
	free(shlvl);
	free(pwd);
}
