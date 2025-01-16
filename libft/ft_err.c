/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:07:40 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:18:14 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_err(const char *msg)
{
	printf("%s\n", msg);
	system("leaks minishell");
	exit(EXIT_FAILURE);
}
