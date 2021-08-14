#include "philosophers.h"

// void init_threads(int num_phs, t_elem *phs)
// {
// 	int	i;
// 	pthread_t warden;

// 	i = 0;
// 	while (i < num_phs)
// 	{
// 		pthread_create(&phs[i].th_id, NULL, live_cycle, &phs[i]);
// 		pthread_join(phs[i].th_id, NULL); // !
// 		i++;
// 	}
// 	pthread_create(&warden, NULL, watch, phs);
// 	pthread_join(warden, NULL);
// }

int	main(int argc, char **argv)
{
	int			num_phs;
	t_elem		*phs;

	if (argc != 5 && argc != 6)
		exit (0);
	num_phs = (int)ft_ll_atoi(argv[1]);
	if (num_phs <= 0)
		return (0); // !
	phs = make_phs_list(argv, num_phs);
	init_mutexes(phs);
	init_threads(phs);
	return (num_phs);
}
