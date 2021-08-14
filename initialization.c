#include "philosophers.h"

t_elem	*new_elem(int i, char **argv, struct timeval *start)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof (t_elem));
	new->ph_id = i;
	new->ttl = ft_ll_atoi(argv[2]);
	new->const_ttl = new->ttl;
	new->tte = ft_ll_atoi(argv[3]);
	new->tts = ft_ll_atoi(argv[4]);
	new->start = *start;
	new->next = NULL;
	new->prev = NULL;
	if (new->ttl <= 0 || new->tte <= 0 || new->tts <= 0)
		return (NULL); // !
	return (new);
}

t_elem	*lstlast(t_elem *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	lstadd_back(t_elem **head, t_elem *new)

{
	t_elem	*last;

	if (*head)
	{
		last = lstlast(*head);
		last->next = new;
		last->next->prev = last;
	}
	else
		*head = new;
}

t_elem	*make_phs_list(char **argv, int num_phs)
{
	t_elem				*ph;
	t_elem				*phs;
	int					i;
	struct timeval 		start;

	i = 0;
	phs = NULL;
	gettimeofday(&start, NULL);
	while (i < num_phs)
	{
		ph = new_elem(i + 1, argv, &start);
		lstadd_back(&phs, ph);
		if (i == num_phs - 1)
		{
			phs->prev = ph;
			ph->next = phs;
		}

		i++;
	}
	return (phs);
}
