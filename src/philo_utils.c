/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:34:57 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/25 19:49:53 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_death(t_data *data) 
{
	suseconds_t	since_last_meal;
	int			i;

	while (1)
	{
		i = 0;
		while (i < data->args.n_philo)
		{
			pthread_mutex_lock(&data->meal_lock);
			since_last_meal = get_time(data) - data->p[i].last_meal;
			pthread_mutex_unlock(&data->meal_lock);
			if (since_last_meal >= data->args.t_die && data->p[i].n_eat != 0)
			{
				do_something('d', &data->p[i]);
				pthread_mutex_lock(&data->death_lock);
				data->death = 1;
				pthread_mutex_unlock(&data->death_lock);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	custom_usleep(int t_ms, t_philo *p)
{
	suseconds_t	start;
	suseconds_t	now;

	start = get_time(p->data);
	now = 0;
	while ((now - start) < t_ms)
	{
		if (is_dead(p->data))
			return (0);
		now = get_time(p->data);
		usleep(50);
	}
	return (1);
}

suseconds_t	get_time(t_data *data)
{
	suseconds_t	ms;
	time_t		sec;

	pthread_mutex_lock(&data->time_lock);
	gettimeofday(&data->time_now, NULL);
	if (data->time_from_start.tv_sec == data->time_now.tv_sec)
	{
		ms = (data->time_now.tv_usec
				- data->time_from_start.tv_usec) / 1000;
	}
	else
	{
		sec = data->time_now.tv_sec - data->time_from_start.tv_sec;
		ms = (sec * 1000) + ((data->time_now.tv_usec
					- data->time_from_start.tv_usec) / 1000);
	}
	pthread_mutex_unlock(&data->time_lock);
	return (ms);
}

int	eat_pasta(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	do_something('f', p);
	if (p->left_fork == p->right_fork)
		return (0);
	pthread_mutex_lock(p->right_fork);
	do_something('f', p);
	do_something('e', p);
	pthread_mutex_lock(&p->data->meal_lock);
	p->last_meal = get_time(p->data);
	pthread_mutex_unlock(&p->data->meal_lock);
	if (!custom_usleep(p->data->args.t_eat, p))
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		return (0);
	}
	do_something('s', p);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (1);
}

int	do_something(char something, t_philo *p)
{
	pthread_mutex_lock(&p->data->message_queue);
	if (is_dead(p->data))
	{
		pthread_mutex_unlock(&p->data->message_queue);
		return (0);
	}
	if (something == 'f')
		printf("%ld %d has taken a fork\n", get_time(p->data), p->id);
	else if (something == 'e')
		printf("%ld %d is eating\n", get_time(p->data), p->id);
	else if (something == 's')
		printf("%ld %d is sleeping\n", get_time(p->data), p->id);
	else if (something == 't')
		printf("%ld %d is thinking\n", get_time(p->data), p->id);
	else if (something == 'd')
		printf("%ld %d died\n", get_time(p->data), p->id);
	pthread_mutex_unlock(&p->data->message_queue);
	return (1);
}
