/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:32:31 by vimercie          #+#    #+#             */
/*   Updated: 2022/11/02 15:44:41 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *arg)
{
	int	i;

	i = *(int *)arg;
	dprintf(1, "test 1: philo_id = %d\n", i);
	usleep(500000);
	dprintf(1, "\n");
	usleep(500000);
	dprintf(1, "test 2: philo_id = %d\n", i);
	free(arg);
	return (0);
}

int	thread_init(t_data *data)
{
	pthread_t	*threads;
	t_philo		p;
	int			i;

	i = 0;
	threads = malloc(data->n_philo * sizeof(pthread_t));
	if (threads == NULL)
		return (0);
	while (i < data->n_philo)
	{
		// allocation de la zone mémoire de l'argument passé à la routine
		p.philo_id = malloc(sizeof(int));
		if (p.philo_id == NULL)
			return (0);
		*p.philo_id = i;
		// création du thread du philo n.[i]
		if (pthread_create(&threads[i], NULL, &philo_routine, p.philo_id) != 0)
			return (0);
		i++;
	}
	i = 0;
	// boucle d'attente de la fin des threads
	while (i < data->n_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (0);
		i++;
	}
	return (0);
}
