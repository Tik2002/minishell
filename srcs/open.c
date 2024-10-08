/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:26:04 by tigpetro          #+#    #+#             */
/*   Updated: 2024/09/01 21:34:40 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_open(int *fd, char *filename, int option)
{
	if (O_RDONLY == option)
		*fd = open(filename, O_RDONLY);
	else
		*fd = open(filename, option, 0644);
	return (*fd != -1);
}
