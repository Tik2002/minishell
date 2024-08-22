/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descriptor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:16:15 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/17 15:54:04 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_descriptor	*make_descriptors(void)
{
	t_descriptor	*res;

	res = wrapper_malloc(sizeof(t_descriptor));
	res->stdout = dup(STDOUT_FILENO);
	res->stdin = dup(STDIN_FILENO);
	res->stderr = dup(STDERR_FILENO);
	return (res);
}
