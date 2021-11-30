/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frodney <frodney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:37:21 by frodney           #+#    #+#             */
/*   Updated: 2021/08/22 14:05:37 by frodney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_elem		*phs;
	t_elem		*filler;

	if (argc != 5 && argc != 6)
	{
		printf("%s", ERR_USAGE);
		return (-1);
	}
	filler = contenting(argv, argc);
	if (!filler)
		return (-1);
	phs = create_table(argv, filler);
	free (filler);
	if (!phs || !init_mutexes(phs) || !init_threads(phs))
	{
		freesh(phs);
		return (-1);
	}
	freesh(phs);
	return (0);
}
