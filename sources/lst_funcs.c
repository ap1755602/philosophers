/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:59:25 by frodney           #+#    #+#             */
/*   Updated: 2021/08/18 18:59:26 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_elem	*new_elem(void)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof (t_elem));
	if (!new)
	{
		printf ("%s", ERR_MALLOC);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_elem	*lstlast(t_elem *lst)
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
