/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:49:39 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/29 16:45:32 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__util__(char *name, char *err)
{
	ft_err_msg(NULL);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	set_status_unsigned(126);
}

static bool	__more_check__(char *script)
{
	set_status_unsigned(0);
	if (!access(script, F_OK | X_OK))
		return (true);
	if (access(script, F_OK))
		__util__(script, ": No such file or directory");
	else if (access(script, X_OK))
		__util__(script, ": Permission denied");
	return (false);
}

bool	ft_check_script(char *script, t_bs_tree_ptr tree)
{
	if (ft_check_cmp(script, "."))
	{
		__util__(script, ": filename argument required");
		set_status_unsigned(2);
		return (false);
	}
	if (chdir(script) == 0)
	{
		chdir(get_tr(tree, "PWD"));
		__util__(script, ": is a directory");
		return (false);
	}
	if (ft_check_cmp(script + ft_strlen(script) - 1, "/"))
	{
		__util__(script, ": Not a directory");
		return (false);
	}
	return (__more_check__(script));
}
