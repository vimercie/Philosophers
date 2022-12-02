/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:32:31 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/02 07:00:56 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_dead(t_philo *p)
{
	p->time.time_in_ms = get_time(p);
	if (p->time.time_in_ms - p->time.end_of_meal >= p->data->args.t_die)
	{
		if (*p->data->stop == 1)
			return (0);
		pthread_mutex_lock(p->data->exit);
		*p->data->stop = 1;
		usleep(1000);
		p->time.time_in_ms = get_time(p);
		printf("%ld %d died\n", p->time.time_in_ms, *p->philo_id);
		pthread_mutex_unlock(p->data->exit);
		return (1);
	}
	return (0);
}

int	do_something(char something, t_philo *p)
{
	if (*p->data->stop == 1)
		return (0);
	p->time.time_in_ms = get_time(p);
	if (something == 'f')
		printf("%ld %d has taken a fork\n", p->time.time_in_ms, *p->philo_id);
	else if (something == 'e')
	{
		printf("%ld %d is eating\n", p->time.time_in_ms, *p->philo_id);
		custom_usleep(p->data->args.t_eat, p);
	}
	else if (something == 's')
	{
		printf("%ld %d is sleeping\n", p->time.time_in_ms, *p->philo_id);
		custom_usleep(p->data->args.t_sleep, p);
	}
	else if (something == 't')
		printf("%ld %d is thinking\n", p->time.time_in_ms, *p->philo_id);
	return (1);
}

int	take_forks(t_philo *p)
{
	if (*p->philo_id % 2 == 0)
	{
		pthread_mutex_lock(p->left_fork);
		if (p->right_fork == p->left_fork)
		{
			pthread_mutex_unlock(p->left_fork);
			return (0);
		}
		do_something('f', p);
		pthread_mutex_lock(p->right_fork);
		do_something('f', p);
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		if (p->right_fork == p->left_fork)
		{
			pthread_mutex_unlock(p->right_fork);
			return (0);
		}
		do_something('f', p);
		pthread_mutex_lock(p->left_fork);
		do_something('f', p);
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo			*p;

	p = (t_philo *)arg;
	p->time.time_in_ms = get_time(p);
	p->time.end_of_meal = 0;
	while (1)
	{
		if (*p->data->stop == 1)
			break;
		take_forks(p);
		do_something('e', p);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		p->time.time_in_ms = get_time(p);
		p->time.end_of_meal = p->time.time_in_ms;
		do_something('s', p);
		do_something('t', p);
		if (is_dead(p))
			break;
	}
	free_philo(p);
	return (0);
}

int	thread_init(t_data *data)
{
	gettimeofday(&data->time_from_start, NULL);
	while (data->i < data->args.n_philo)
	{
		if (!philo_init(data, data->i))
		{
			while(data->i >= 0)
			{
				free_philo(&data->p[data->i]);
				data->i--;
			}
			return (-1);
		}
		if (pthread_create(&data->threads[data->i], NULL, &philo_routine, &data->p[data->i]) != 0)
			return (0);
		data->i++;
	}
	data->i = 0;
	while (data->i < data->args.n_philo)
	{
		if (pthread_join(data->threads[data->i], NULL) != 0)
			return (0);
		data->i++;
	}
	free_data(data);
	return (1);
}
