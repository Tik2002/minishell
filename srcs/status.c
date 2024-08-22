/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:09:53 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 11:59:22 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_status;

void	set_status_unsigned(int status)
{
	g_status = (const unsigned char)status;
}

void	set_status_signed(int status)
{
	g_status = (const char)status;
}

int	get_status(void)
{
	return (g_status);
}
