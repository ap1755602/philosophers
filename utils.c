#include "philosophers.h"

long long	ft_ll_atoi(const char *s)
{
	int		minus;
	long long	res;
	int		i;

	minus = 1;
	res = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			minus = -minus;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9' && s[i])
	{
		res *= 10;
		res += (s[i] - '0');
		i++;
	}
	res *= minus;
	return (res);
}

long long	diff_time_ms(struct timeval *start)
{
	struct timeval	end;
	long long		res;

	gettimeofday(&end, NULL);
	res = (((end.tv_sec * 1000000 + end.tv_usec) -\
		(start->tv_sec * 1000000 + start->tv_usec))/1000);
	return (res);
}