/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:41:44 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:08:50 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	char	*tmp_dup;

	dup = (char *)malloc(ft_strlen(src) + 1);
	if (!dup)
		return (0);
	tmp_dup = dup;
	while (src && *src)
	{
		*dup = *src;
		++dup;
		++src;
	}
	*dup = '\0';
	return (tmp_dup);
}
