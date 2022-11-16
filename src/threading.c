/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:32:31 by vimercie          #+#    #+#             */
/*   Updated: 2022/11/16 13:49:17 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *arg)
{
	t_philo		*p;
	suseconds_t	time_in_ms;
	suseconds_t	end_of_meal;
	int			n_meal;
	int			laps;

	p = (t_philo *)arg;
	time_in_ms = get_time(p);
	end_of_meal = 0;
	n_meal = 0;
	laps = 1;
	while (1)
	{
		while (n_meal < laps && laps < 10)
		{
			// take time
			pthread_mutex_lock(p->right_fork);
			time_in_ms = get_time(p);
			dprintf(1, "%ld %d has taken right fork\n", time_in_ms, *p->philo_id);
			pthread_mutex_lock(p->left_fork);
			time_in_ms = get_time(p);
			dprintf(1, "%ld %d has taken left fork\n", time_in_ms,*p->philo_id);
			time_in_ms = get_time(p);
			dprintf(1, "%ld %d is eating\n", time_in_ms, *p->philo_id);
			custom_usleep(p->t_eat, p);
			n_meal++;
			pthread_mutex_unlock(p->right_fork);
			pthread_mutex_unlock(p->left_fork);
			dprintf(1, "%d HAS EATEN %d TIMES\n", *p->philo_id, n_meal);
			time_in_ms = get_time(p);
			end_of_meal = time_in_ms;
			dprintf(1, "%ld %d is sleeping\n", time_in_ms, *p->philo_id);
			custom_usleep(p->t_sleep, p);
			time_in_ms = get_time(p);
			dprintf(1, "%ld %d is thinking\n", time_in_ms, *p->philo_id);
		}
		time_in_ms = get_time(p);
		if (time_in_ms - end_of_meal >= p->t_die)
		{
			dprintf(1, "%ld %d DIED !\n", time_in_ms, *p->philo_id);
			return (0);
		}
		laps++;
	}
	free(p->philo_id);
	return (0);
}

int	thread_init(t_data *data)
{
	int			i;

	i = 0;
	if (!data_init(data))
		return (0);
	while (i < data->n_philo)
	{
		philo_init(data, i);
		if (pthread_create(&data->threads[i], NULL, &philo_routine, &data->p[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			return (0);
		i++;
	}
	free(data->threads);
	free(data->p);
	free(data->forks_id);
	return (0);
}
