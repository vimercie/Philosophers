/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:34:57 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/13 12:15:05 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	custom_usleep(int time_in_ms, t_philo *p)
{
	int	start;
	int	now;

	start = get_time(p);
	now = 0;
	while ((now - start) < time_in_ms)
	{
		now = get_time(p);
		if (is_dead(p) || *p->data->death == 1)
		{
			do_something('d', p);
			return (0);
		}
		usleep(50);
	}
	return (1);
}

int	get_time(t_philo *p)
{
	suseconds_t	ms;
	time_t		sec;

	gettimeofday(&p->time.time_now, NULL);
	if (p->time.time_from_start->tv_sec == p->time.time_now.tv_sec)
		ms = (p->time.time_now.tv_usec
				- p->time.time_from_start->tv_usec) / 1000;
	else
	{
		sec = p->time.time_now.tv_sec - p->time.time_from_start->tv_sec;
		ms = (sec * 1000) + ((p->time.time_now.tv_usec
					- p->time.time_from_start->tv_usec) / 1000);
	}
	return (ms);
}

int	print_action(char something, t_philo *p)
{
	p->time.time_in_ms = get_time(p);
	if (something == 'f')
		printf("%d %d has taken a fork\n", p->time.time_in_ms, *p->philo_id);
	else if (something == 'e')
		printf("%d %d is eating\n", p->time.time_in_ms, *p->philo_id);
	else if (something == 's')
		printf("%d %d is sleeping\n", p->time.time_in_ms, *p->philo_id);
	else if (something == 't')
		printf("%d %d is thinking\n", p->time.time_in_ms, *p->philo_id);
	else if (something == 'd')
	{
		printf("%d %d died\n", p->time.time_in_ms, *p->philo_id);
		*p->data->death = 1;
	}
	return (1);
}

int	do_something(char something, t_philo *p)
{
	pthread_mutex_lock(p->data->message_queue);
	if (*p->data->death == 1)
	{
		pthread_mutex_unlock(p->data->message_queue);
		return (0);
	}
	if (is_dead(p))
	{
		print_action('d', p);
		pthread_mutex_unlock(p->data->message_queue);
		return (0);
	}
	print_action(something, p);
	if (something == 'e')
		p->time.last_meal = get_time(p);
	pthread_mutex_unlock(p->data->message_queue);
	return (1);
}
