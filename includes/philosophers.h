/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:25:35 by frodney           #+#    #+#             */
/*   Updated: 2021/08/21 22:45:02 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERR_MALLOC "error: memory was'n allocated\n"
# define ERR_USAGE "usage: ./philosophers <number of philosophers> <time to live> <time to eat> \
<time to sleep> <count meals>\n"

typedef struct s_data
{
	int					count;
	int					ttl;
	int					tte;
	int					tts;
	struct timeval		start;
}	t_data;

typedef struct s_mutexes
{
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*uni;
}	t_mutexes;

typedef struct s_elem
{
	int					ph_id;
	int					dinners;
	long long			diff_start;
	pthread_t			th_id;
	t_mutexes			*m;
	t_data				*etq;
	struct s_elem		*prev;
	struct s_elem		*next;
}	t_elem;

int						ft_atoi(const char *s);
int						main(int argc, char **argv);
void					*live_cycle(void *arg);
void					*warding(void *arg);
t_elem					*create_table(char **argv, t_elem *filler);
void					freesh(t_elem *phs);
int						init_mutexes(t_elem *phs);
int						init_threads(t_elem *phs);
long long				diff_time_usec(struct timeval *start);
void					delay(long long ms);
long long				cur_time(void);
t_elem					*contenting(char **argv, int argc);
void					lstadd_back(t_elem **head, t_elem *new);
t_elem					*new_elem(void);

#endif
