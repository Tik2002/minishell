/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:08:10 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/29 16:04:39 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	__update_pwd__(t_minishell *minishell, char *pwd, char *oldpwd)
{
	update_tr(minishell->export, "OLDPWD", oldpwd, true);
	update_tr(minishell->export, "PWD", pwd, true);
}

static bool	__ft_cd__(char *path, int size)
{
	char	*oldpwd;

	oldpwd = __ft_pwd__();
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": directory does not exist", STDERR_FILENO);
		free(oldpwd);
		return (false);
	}
	if (size == 1 && errno == ENOENT)
	{
		ft_err_msg("cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory");
		free(oldpwd);
		return (false);
	}
	if (size > 1)
		chdir(oldpwd);
	free(oldpwd);
	return (size == 1);
}

static char	*__get_home__(t_bs_tree_ptr export)
{
	char	*tmp;

	tmp = get_tr(export, "HOME");
	if (!tmp)
		ft_err_msg("cd: HOME not set");
	return (tmp);
}

static void	__eval__(t_command *cmd, char *oldpwd, int *status, int size)
{
	char	*pwd;

	if (cmd->opts.head && ft_check_cmp(cmd->opts.head->val, "-"))
	{
		pwd = get_tr(cmd->minishell->export, "OLDPWD");
		if (pwd)
			printf("%s\n", pwd);
		else
			ft_err_msg("cd: OLDPWD not set");
	}
	else if (cmd->opts.head)
		pwd = cmd->opts.head->val;
	else
		pwd = __get_home__(cmd->minishell->export);
	if (!pwd)
		return ;
	if (!__ft_cd__(pwd, size))
		return ;
	pwd = __ft_pwd__();
	*status = 0;
	if (!ft_check_cmp(oldpwd, pwd))
		__update_pwd__(cmd->minishell, pwd, oldpwd);
	free(pwd);
}

void	ft_cd(t_command *cmd, int size)
{
	char	*oldpwd;
	int		status;

	status = 1;
	move_back_lt(&cmd->opts, &cmd->args);
	oldpwd = get_tr(cmd->minishell->export, "PWD");
	if (!cmd->opts.head || (cmd->opts.head && (ft_check_cmp(cmd->opts.head->val,
					"-") || cmd->opts.head->val[0] != '-')))
		__eval__(cmd, oldpwd, &status, size);
	else if (cmd->opts.head)
	{
		ft_err_msg("cd: no option required");
		status = 2;
	}
	set_status_unsigned(status);
}
