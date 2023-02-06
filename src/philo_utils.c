/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:34:57 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/06 06:25:20 by vimercie         ###   ########.fr       */
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

int	check_stop(t_data *data)
{
	int	n_hungry_philo;
	int	i;

	while (1)
	{
		i = 0;
		n_hungry_philo = data->args.n_philo;
		while (i < data->args.n_philo)
		{
			pthread_mutex_lock(&data->n_eat_lock);
			if (data->p[i].n_eat == 0)
				n_hungry_philo--;
			pthread_mutex_unlock(&data->n_eat_lock);
			i++;
		}
		i = 0;
		if (n_hungry_philo == 0)
			break ;
		if (check_death(data, i))
		{
			do_something('d', &data->p[i]);
			break ;
		}
		i++;
	}
	pthread_mutex_lock(&data->stop_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_lock);
	return (1);
}

int	check_death(t_data *data, int id)
{
	suseconds_t	since_last_meal;

	pthread_mutex_lock(&data->last_meal_lock);
	since_last_meal = get_time(data) - data->p[id].last_meal;
	pthread_mutex_unlock(&data->last_meal_lock);
	if (since_last_meal >= data->args.t_die)
		return (1);
	return (0);
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
		printf("is eating\n");
	else if (something == 's')
		printf("is sleeping\n");
	else if (something == 't')
		printf("is thinking\n");
	else if (something == 'd')
		printf("died\n");
	pthread_mutex_unlock(&p->data->message_queue);
	return (1);
}
