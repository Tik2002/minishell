/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_delimitors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:10:38 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/29 16:04:39 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*__make_string__(char *str, int end)
{
	char	*res;

	res = ft_substr(str, 0, end);
	if (!res)
		_err("Malloc error\n");
	return (res);
}

static int	__chars_counter__(char *input, char *del)
{
	int	res;

	res = 0;
	while (input[res] && !ft_strchr(del, input[res]))
		res++;
	if (!res)
		return (1);
	return (res);
}

void	ft_split_with_delim(t_list_ptr line, char *del, char *input)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		j = __chars_counter__(input + i, del);
		str = __make_string__(input + i, j);
		i += j;
		push_back_lt(line, str);
		free(str);
	}
}
