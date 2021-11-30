/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:10:46 by frodney           #+#    #+#             */
/*   Updated: 2021/08/17 14:10:47 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	validate_atoi(long long res, char c)
{
	if (res < -2147483648 || res > 2147483647)
		printf("%s", "error: return value of atoi more than max or min int\n");
	else if (c != '\0')
	{
		printf ("%s", ERR_USAGE);
		return (0);
	}
	else if (res <= 0)
		printf("%s", "error: args shouldn't be <= 0\n");
	else
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	int			minus;
	long long	res;
	int			i;

	minus = 1;
	res = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			minus = -minus;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res *= 10;
		res += (s[i] - '0');
		i++;
	}
	res *= minus;
	if (!validate_atoi(res, s[i]))
		return (0);
	return ((int)res);
}
