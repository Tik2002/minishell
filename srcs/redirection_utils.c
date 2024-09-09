/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:22:44 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/09 16:24:41 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	__redir_util__(char *print)
{
	ft_err_msg(NULL);
	ft_putstr_fd(print, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}
