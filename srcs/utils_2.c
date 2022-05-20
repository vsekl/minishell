/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:31:26 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 16:51:01 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

static int	ft_is_num_2(char *str, int sign)
{
	long long	sum;

	sum = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		if (!sign)
		{
			if ((sum * (-1) == -922337203685477580LL && *str > '8') || \
					sum * (-1) < -922337203685477580LL)
				return (0);
		}
		else if ((sum == 922337203685477580LL && *str > '7') || \
					(sum > 922337203685477580LL))
			return (0);
		sum = sum * 10 + (*str - '0');
		str++;
	}
	return (1);
}

int	ft_is_num(char *str)
{
	int			sign;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = 0;
		str++;
	}
	return (ft_is_num_2(str, sign));
}

char	*find_str(char **array, char *str)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		if (!ft_strncmp(array[i], str, ft_strlen(str)))
			return (array[i]);
		i++;
	}
	return (NULL);
}

int	ft_wexitstatus(int x)
{
	return ((x >> 8) & 0x000000ff);
}
