/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:30:08 by frodney           #+#    #+#             */
/*   Updated: 2021/08/22 14:06:27 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_everything(t_elem *phs)
{
	t_elem	*tmp;

	tmp = NULL;
	while (phs)
	{
		tmp = phs->next;
		if (phs->m->left_fork)
		{
			pthread_mutex_destroy(phs->m->left_fork);
			free (phs->m->left_fork);
			phs->m->left_fork = NULL;
			free (phs->m);
			phs->m = NULL;
		}
		if (phs->prev)
			phs->prev = NULL;
		phs->next = NULL;
		free(phs);
		phs = NULL;
		phs = tmp;
	}
}

void	freesh(t_elem *phs)
{
	if (phs && phs->prev)
		phs->prev->next = NULL;
	if (phs && phs->m->uni)
		pthread_mutex_destroy(phs->m->uni), free(phs->m->uni);
	if (phs->etq)
		free (phs->etq);
	free_everything(phs);
}
