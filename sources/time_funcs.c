/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:16:09 by frodney           #+#    #+#             */
/*   Updated: 2021/08/17 14:16:18 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	diff_time_usec(struct timeval *start)
{
	struct timeval	end;
	struct timeval	diff;

	gettimeofday(&end, NULL);
	diff.tv_sec = end.tv_sec - start->tv_sec;
	diff.tv_usec = end.tv_usec - start->tv_usec;
	if (diff.tv_usec < 0)
	{
		diff.tv_sec--;
		diff.tv_usec += 1000000;
	}
	return ((diff.tv_sec * 1000000) + diff.tv_usec);
}

long long	cur_time(void)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (cur.tv_sec * 1000000 + cur.tv_usec);
}

void	delay(long long time)
{
	long long	stop;

	stop = cur_time() + (time * 1000);
	while (cur_time() < stop)
		usleep(100);
}
