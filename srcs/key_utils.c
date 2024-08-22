/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:29:07 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/17 15:54:55 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	__is_valid_key__(char c)
{
	return (c == '_' || ft_isalnum(c));
}

bool	__check_key__(char *val)
{
	int	i;

	if (val[0] != '_' && !ft_isalpha(val[0]))
		return (false);
	i = 1;
	while (val[i] != '\0' && val[i] != '=')
	{
		if (!__is_valid_key__(val[i]))
			return (false);
		++i;
	}
	return (true);
}

int	__strlen_till__(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (1);
	while (__is_valid_key__(str[i]))
		++i;
	return (i);
}

int	__strlen_till_dollar__(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$')
		++i;
	return (i);
}

int	__counter__(char *str, char c)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i])
		if (str[i] == c)
			++res;
	return (res);
}
