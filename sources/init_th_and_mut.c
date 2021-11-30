/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_th_and_mut.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:39:22 by frodney           #+#    #+#             */
/*   Updated: 2021/08/22 14:21:09 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_elem *phs)
{
	pthread_t	ward;

	if (pthread_create(&phs->th_id, NULL, live_cycle, phs) < 0)
		return (0);
	phs = phs->next;
	while (phs->ph_id > phs->prev->ph_id)
	{
		if (pthread_create(&phs->th_id, NULL, live_cycle, phs) < 0)
			return (0);
		phs = phs->next;
	}
	if (pthread_create(&ward, NULL, warding, phs) < 0)
		return (0);
	pthread_join(ward, NULL);
	return (1);
}

int	init_mutexes(t_elem *phs)
{
	int					i;
	pthread_mutex_t		*uni;

	i = 1;
	uni = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t));
	pthread_mutex_init(uni, NULL);
	while (i <= phs->etq->count)
	{
		phs->m->uni = uni;
		phs->m->left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!phs->m->left_fork)
		{
			printf("%s", ERR_MALLOC);
			return (0);
		}
		pthread_mutex_init(phs->m->left_fork, NULL);
		phs->prev->m->right_fork = phs->m->left_fork;
		phs = phs->next;
		i++;
	}
	return (1);
}
