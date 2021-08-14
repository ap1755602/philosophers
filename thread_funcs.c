#include "philosophers.h"

void*	live_cycle(void *arg)
{
	t_elem	*ph;
	struct timeval	cur;

	ph = (t_elem *)arg;
	while (1)
	{
		ph->ttl = ph->const_ttl;
		printf ("%-3lldms\tPhilosopher %d is eating\n", diff_time_ms(&ph->start), 
			ph->ph_id);
		usleep(ph->tte * 1000);
		printf ("%-3lldms\tPhilosopher %d is sleeping\n", diff_time_ms(&ph->start), 
			ph->ph_id);
		usleep(ph->tts * 1000);
	}
	return (NULL);
}

void*	watch(void *arg)
{
	t_elem	*tmp;

	t_elem	*phs;
	struct timeval	start;
	struct timeval	end;
	long			res;
	int		i;

	phs = (t_elem *)arg;
	i = 16;
	res = 0;
	// tmp = phs;
	while (i)
	{
		gettimeofday(&start, NULL);
		usleep (100000);
		res = diff_time_ms(&start);
		phs->ttl -= res;
		if(phs->ttl < 0)
		{
			printf ("%-3lldms\tPhilosopher %d is dead\n", diff_time_ms(&phs->start), 
			phs->ph_id);
			exit(0);
		}
			
		i--;
	}

	phs = tmp;
	return (NULL);
}

void	init_threads(t_elem *phs)
{
	pthread_t warden;

	pthread_create(&phs->th_id, NULL, live_cycle, phs);
	// pthread_join(phs->th_id, NULL); // !
	phs = phs->next;
	while (phs->ph_id > phs->prev->ph_id)
	{
		pthread_create(&phs->th_id, NULL, live_cycle, phs);
		// pthread_detach(phs->th_id);
		// pthread_join(phs->th_id, NULL); // !
		phs = phs->next;
	}
	printf("================================\n");
	pthread_create(&warden, NULL, watch, phs);
	pthread_join(warden, NULL);
}

void	init_mutexes(t_elem *phs) // только для 2 и более флсфв
{
	int	flag;

	flag = 0;
	while (phs->prev->ph_id < phs->ph_id || !flag)
	{
		flag = 1;
		phs->left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(phs->left_fork, NULL);
		phs->prev->right_fork = phs->left_fork;
		phs = phs->next;
	}
}