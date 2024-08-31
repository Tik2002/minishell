/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:49:39 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/31 19:29:42 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__util__(char *name, char *err, char **oldpwd)
{
	ft_err_msg(NULL);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	free(*oldpwd);
	*oldpwd = NULL;
	set_status_unsigned(126);
}

static bool	__more_check__(char *script, char **oldpwd)
{
	set_status_unsigned(0);
	if (!access(script, F_OK | X_OK))
	{
		free(*oldpwd);
		*oldpwd = NULL;
		return (true);
	}
	if (access(script, F_OK))
		__util__(script, ": No such file or directory", oldpwd);
	else if (access(script, X_OK))
		__util__(script, ": Permission denied", oldpwd);
	return (false);
}

bool	ft_check_script(char *script, t_bs_tree_ptr tree)
{
	char	*oldpwd;

	oldpwd = __ft_pwd__();
	if (ft_check_cmp(script, "."))
	{
		__util__(script, ": filename argument required", &oldpwd);
		set_status_unsigned(2);
		return (false);
	}
	if (chdir(script) == 0)
	{
		chdir(get_tr(tree, "PWD"));
		__util__(script, ": is a directory", &oldpwd);
		return (false);
	}
	if (ft_check_cmp(script + ft_strlen(script) - 1, "/"))
	{
		__util__(script, ": Not a directory", &oldpwd);
		return (false);
	}
	return (__more_check__(script, &oldpwd));
}
