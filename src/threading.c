/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:32:31 by vimercie          #+#    #+#             */
/*   Updated: 2022/10/31 15:12:35 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = arg;
	dprintf(1, "TEST n:%d\n", p->philo_id);
	return (0);
}

int	thread_init(t_data *data)
{
	pthread_t	*threads;
	t_philo		p;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->n_philo);
	while (i < data->n_philo)
	{
		p.philo_id = i;
		pthread_create(threads + i, NULL, &philo_routine, &p);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
