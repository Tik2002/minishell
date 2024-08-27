/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:30:25 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/26 15:30:39 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_get_path(char *path)
{
	char	**path_mtx;

	if (!path)
		return (NULL);
	path_mtx = ft_split(path, ':');
	return (path_mtx);
}
