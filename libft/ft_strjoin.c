/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:18:25 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:08:50 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	all_size;
	size_t	i;
	char	*res;

	if (!s1 || !s2)
		return (0);
	all_size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	res = (char *)malloc((all_size + 1) * sizeof(char));
	if (res == 0)
		return (0);
	while (*s1)
	{
		res[i] = *s1;
		++i;
		++s1;
	}
	while (*s2)
	{
		res[i] = *s2;
		++i;
		++s2;
	}
	res[i] = '\0';
	return (res);
}
