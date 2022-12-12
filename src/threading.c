/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:32:31 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/12 22:43:25 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	exit_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_philo)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			return (0);
		pthread_mutex_destroy(&data->forks_id[i]);
		i++;
	}
	return (1);
}

void	*one_philo(void *arg)
{
	t_philo			*p;

	p = (t_philo *)arg;
	p->time.last_meal = 0;
	p->time.time_in_ms = get_time(p);
	do_something('f', p);
	while (*p->data->death == 0)
	{
		if (is_dead(p))
			do_something('d', p);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo			*p;

	p = (t_philo *)arg;
	p->time.last_meal = 0;
	if (*p->philo_id % 2 == 0)
		custom_usleep(p->data->args.t_eat, p);
	while (*p->data->death == 0)
	{
		pthread_mutex_lock(p->left_fork);
		do_something('f', p);
		pthread_mutex_lock(p->right_fork);
		do_something('f', p);
		do_something('e', p);
		p->time.last_meal = get_time(p);
		*p->n_eat -= 1;
		if (*p->n_eat == 0 && *p->data->argc == 6)
			break ;
		custom_usleep(p->data->args.t_eat, p);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		do_something('s', p);
		custom_usleep(p->data->args.t_sleep, p);
		do_something('t', p);
	}
	if (*p->n_eat == 0 && *p->data->argc == 6)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
	return (0);
}

int	threading(t_data *data)
{
	int	i;

	i = 0;
	if (data->args.n_philo == 1)
	{
		if (pthread_create(&data->threads[0], NULL,
				&one_philo, &data->p[0]) != 0)
			return (0);
	}
	else
	{
		while (i < data->args.n_philo)
		{
			if (pthread_create(&data->threads[i], NULL,
					&philo_routine, &data->p[i]) != 0)
				return (0);
			i++;
		}
	}
	exit_philo(data);
	return (1);
}
