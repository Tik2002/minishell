/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:43:38 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/12 19:32:06 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	__strlen__(char *src)
{
	int	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i])
		i++;
	return (i);
}

void	ft_append(char **left, char *right)
{
	char	*res;
	int		i;
	int		y;
	int		k;

	if ((!left || !*left) && !right)
		return ;
	i = __strlen__(*left);
	y = __strlen__(right);
	res = wrapper_malloc(i + y + 1);
	res[i + y] = '\0';
	k = -1;
	while (++k < i)
		res[k] = (*left)[k];
	k = -1;
	while (++k < y)
		res[i + k] = right[k];
	free(*left);
	*left = res;
}
