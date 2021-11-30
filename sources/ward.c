/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ward.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:23:39 by frodney           #+#    #+#             */
/*   Updated: 2021/08/22 14:33:37 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	chase(t_elem *phs, int *hungry_phs)
{
	long long		now;
	int				i;

	now = 0;
	i = 0;
	while (i < phs->etq->count)
	{
		now = diff_time_usec(&phs->etq->start);
		now -= phs->diff_start;
		if (phs->dinners == 0)
			(*hungry_phs)--;
		else if (now > phs->etq->ttl * 1000)
		{
			pthread_mutex_lock(phs->m->uni);
			printf ("%-10lldms\t%d died\n", \
			(diff_time_usec(&phs->etq->start) / 1000), phs->ph_id);
			return (1);
		}
		phs = phs->next, i++;
	}
	return (0);
}

void	*warding(void *arg)
{
	t_elem		*phs;
	int			hungry_phs;

	phs = (t_elem *)arg;
	while (1)
	{
		usleep (500);
		hungry_phs = phs->etq->count;
		if (chase (phs, &hungry_phs))
			return (NULL);
		if (hungry_phs == 0)
		{
			pthread_mutex_lock(phs->m->uni);
			printf ("vse sity :)\n");
			return (NULL);
		}
	}
	return (NULL);
}
