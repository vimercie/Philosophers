/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:34:57 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/12 23:53:25 by vimercie         ###   ########.fr       */
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
		if (is_dead(p))
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
		printf("%ld %d has taken a fork\n", p->time.time_in_ms, *p->philo_id);
	else if (something == 'e')
	{
		printf("%ld %d is eating\n", p->time.time_in_ms, *p->philo_id);
		p->time.last_meal = p->time.time_in_ms;
	}
	else if (something == 's')
		printf("%ld %d is sleeping\n", p->time.time_in_ms, *p->philo_id);
	else if (something == 't')
		printf("%ld %d is thinking\n", p->time.time_in_ms, *p->philo_id);
	else if (something == 'd')
	{
		printf("%ld %d died\n", p->time.time_in_ms, *p->philo_id);
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
	pthread_mutex_unlock(p->data->message_queue);
	return (1);
}
