/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:01:10 by tyavroya          #+#    #+#             */
/*   Updated: 2024/08/12 17:22:45 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_whitespace(const char ch)
{
	return (ch == '\t' || ch == ' ' || ch == '\v'
		|| ch == '\n' || ch == '\f' || ch == '\r');
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while (is_whitespace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = (-1) * sign;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		++i;
	}
	return (sign * res);
}
