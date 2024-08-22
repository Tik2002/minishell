/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigpetro <tigpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:00:53 by tigpetro          #+#    #+#             */
/*   Updated: 2024/08/22 12:58:59 by tigpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_split_to_list(t_list_ptr list, char del, char *input)
{
	int		i;
	char	**str;

	str = ft_split(input, del);
	i = -1;
	while (str[++i])
		push_back_lt(list, str[i]);
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	ft_err_msg(char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (msg && *msg)
		ft_putendl_fd(msg, STDERR_FILENO);
}

static bool	ft_strncmp_msh(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (false);
	if (!s1 || !s2)
		return (true);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		++i;
	}
	return (i != n || (s1[i] && s1[i] != '\n'));
}

static int	__max_len__(char *s1, char *s2)
{
	int	i;
	int	y;

	i = ft_strlen(s1);
	y = ft_strlen(s2);
	if (i > y)
		return (i);
	return (y);
}

bool	ft_check_cmp(char *s1, char *s2)
{
	return (!ft_strncmp_msh(s1, s2, __max_len__(s1, s2)));
}
