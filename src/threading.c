/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:32:31 by vimercie          #+#    #+#             */
/*   Updated: 2022/11/08 20:03:12 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *arg)
{
	t_philo		*p;
	suseconds_t	n;

	p = (t_philo *)arg;
	n = get_time(p);
	pthread_mutex_lock(p->right_fork);
	dprintf(1, "%ld %d has taken a fork\n", n, *p->philo_id);
	pthread_mutex_lock(p->left_fork);
	dprintf(1, "%ld %d has taken a fork\n", n,*p->philo_id);
	n = get_time(p);
	dprintf(1, "%ld %d is eating\n", n, *p->philo_id);
	usleep(p->t_eat * 1000);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
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
