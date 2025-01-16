/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:05:34 by tigpetro          #+#    #+#             */
/*   Updated: 2025/01/15 19:08:50 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_counter(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count = 1;
	else if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		++count;
	}
	return (count);
}

static char	*_the_most_cases(int n)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = _counter(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == 0)
		return (0);
	if (n < 0)
	{
		res[0] = '-';
		n = n * -1;
		++i;
	}
	res[len] = '\0';
	while (i < len)
	{
		--len;
		res[len] = ((n % 10) + '0');
		n /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;

	if (n == INT_MIN)
	{
		res = ft_strdup("-2147483648");
		return (res);
	}
	return (_the_most_cases(n));
}
