#ifndef PHILO_PHILOSOPHERS_H
# define PHILO_PHILOSOPHERS_H

# include <stdlib.h> // ??
# include <stdio.h> // ??
# include <unistd.h> // usleep
# include <pthread.h>
# include <time.h>
# include <sys/time.h> // gettimeofday

typedef struct	s_elem
{
	pthread_t				th_id;
	int						ph_id;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	long long				const_ttl;
	long long 				ttl;
	long long 				tte;
	long long				tts;
	struct timeval			start;
	struct s_elem			*prev;
	struct s_elem			*next;
} t_elem;

long long		ft_ll_atoi(const char *s);
int				main(int argc, char **argv);
void* 			live_cycle(void *arg);
void*			watch(void *arg);
t_elem			*make_phs_list(char **argv, int num_phs);
void			init_mutexes(t_elem *phs);
void			init_threads(t_elem *phs);
long long		diff_time_ms(struct timeval *start);


t_elem	*new_elem(int i, char **argv, struct timeval *start);

#endif
