/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phill.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:00:41 by frodney           #+#    #+#             */
/*   Updated: 2021/08/22 14:31:39 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define EAT " is eating"
#define SLEEP " is sleeping"
#define TAKE_FORK " has taken a fork"
#define THINK " is thinking"

static void	print_massage(char *status, t_elem *ph)
{
	if (!status)
		return ;
	pthread_mutex_lock (ph->m->uni);
	printf ("%-10lldms\t%d%s\n", (diff_time_usec (&ph->etq->start) / 1000), \
		ph->ph_id, status);
	pthread_mutex_unlock (ph->m->uni);
}

static void	pathetic_dinner(t_elem *ph)
{
	if (pthread_mutex_lock (ph->m->right_fork) < 0)
		return ;
	print_massage (TAKE_FORK, ph);
	pthread_mutex_lock (ph->m->left_fork);
	print_massage (TAKE_FORK, ph);
	print_massage (EAT, ph);
	ph->diff_start = diff_time_usec (&ph->etq->start);
	delay (ph->etq->tte);
	pthread_mutex_unlock (ph->m->right_fork);
	pthread_mutex_unlock (ph->m->left_fork);
	if (ph->etq->count % 2)
		usleep(1000);
}

static void	dinner(t_elem *ph)
{
	print_massage (THINK, ph);
	if (ph->ph_id % 2)
	{
		pathetic_dinner(ph);
		return ;
	}
	pthread_mutex_lock (ph->m->left_fork);
	print_massage (TAKE_FORK, ph);
	pthread_mutex_lock (ph->m->right_fork);
	print_massage (TAKE_FORK, ph);
	print_massage (EAT, ph);
	ph->diff_start = diff_time_usec (&ph->etq->start);
	delay (ph->etq->tte);
	pthread_mutex_unlock (ph->m->left_fork);
	pthread_mutex_unlock (ph->m->right_fork);
}

void	*live_cycle(void *arg)
{
	long long		death;
	t_elem			*ph;

	ph = (t_elem *)arg;
	if (ph->ph_id % 2)
		usleep(1500);
	while (1)
	{
		death = diff_time_usec(&ph->etq->start);
		death -= ph->diff_start;
		dinner(ph);
		ph->dinners--;
		if (ph->dinners == 0 || death > ph->etq->ttl * 1000)
			break ;
		print_massage(SLEEP, ph);
		delay(ph->etq->tts);
	}
	return (NULL);
}
