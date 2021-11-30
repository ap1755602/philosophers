/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_filos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 22:27:16 by frodney           #+#    #+#             */
/*   Updated: 2021/08/21 23:21:18 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_elem	*contenting(char **argv, int argc)
{
	t_elem			*f;
	struct timeval	start;

	gettimeofday(&start, NULL);
	f = (t_elem *)malloc(sizeof (t_elem));
	f->etq = (t_data *)malloc(sizeof (t_data));
	if (!f || !f->etq)
	{
		if (!f->etq)
			free (f);
		printf("%s\n", ERR_MALLOC);
		return (NULL);
	}
	f->etq->ttl = ft_atoi(argv[2]);
	f->etq->count = ft_atoi(argv[1]);
	f->etq->tte = ft_atoi(argv[3]);
	f->etq->tts = ft_atoi(argv[4]);
	f->etq->start = start;
	if (argc == 6)
		f->dinners = ft_atoi(argv[5]);
	else
		f->dinners = 2147483647;
	f->diff_start = diff_time_usec(&f->etq->start);
	return (f);
}

int	fill_elem(t_elem *src, t_elem *dst)
{
	static int		i = 1;

	dst->ph_id = i, i++;
	dst->etq = src->etq;
	dst->dinners = src->dinners;
	dst->m = (t_mutexes *) malloc(sizeof (t_mutexes));
	dst->m->right_fork = NULL;
	dst->m->left_fork = NULL;
	dst->diff_start = src->diff_start;
	if (!dst->etq->ttl || !dst->etq->tte || \
	 !dst->etq->tts || !dst->etq->count || !dst->dinners)
		return (0);
	return (1);
}

t_elem	*create_table(char **argv, t_elem *filler)
{
	t_elem	*ph;
	t_elem	*phs;
	int		i;

	i = ft_atoi(argv[1]);
	phs = NULL;
	while (i > 0)
	{
		ph = new_elem();
		if ((!ph) || !fill_elem (filler, ph) || !filler)
		{
			freesh(phs);
			return (NULL);
		}
		lstadd_back(&phs, ph);
		if ((i - 1) == 0)
		{
			phs->prev = ph;
			ph->next = phs;
		}
		ph = NULL, i--;
	}
	return (phs);
}
