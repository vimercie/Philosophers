/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:34:57 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/10 16:10:45 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

int	custom_usleep(int t_ms, t_philo *p)
{
	suseconds_t	start;
	suseconds_t	now;

	start = get_time(p->data);
	now = 0;
	while ((now - start) < t_ms)
	{
		if (is_stop(p->data))
			return (0);
		now = get_time(p->data);
		usleep(50);
	}
	return (1);
}

int	take_forks(t_philo *p)
{
	if (p->id != p->data->args.n_philo)
	{
		pthread_mutex_lock(p->left_fork);
		do_something('f', p);
		pthread_mutex_lock(p->right_fork);
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		do_something('f', p);
		pthread_mutex_lock(p->left_fork);
	}
	do_something('f', p);
	return (0);
}

int	do_something(char something, t_philo *p)
{
	if (is_stop(p->data))
		return (0);
	pthread_mutex_lock(&p->data->message_queue);
	printf("%ld %d ", get_time(p->data), p->id);
	if (something == 'f')
		printf("has taken a fork\n");
	else if (something == 'e')
	{
		printf("is eating\n");
		pthread_mutex_lock(&p->data->last_meal_lock);
		p->last_meal = get_time(p->data);
		pthread_mutex_unlock(&p->data->last_meal_lock);
	}
	else if (something == 's')
		printf("is sleeping\n");
	else if (something == 't')
		printf("is thinking\n");
	else if (something == 'd')
		printf("died\n");
	pthread_mutex_unlock(&p->data->message_queue);
	return (1);
}
