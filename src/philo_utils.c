/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:34:57 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/14 16:46:11 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	custom_usleep(int time_in_ms, t_philo *p)
{
	int	start;
	int	now;

	start = get_time(p, *p->philo_id - 1);
	now = 0;
	while ((now - start) < time_in_ms)
	{
		now = get_time(p, *p->philo_id - 1);
		usleep(50);
	}
	return (1);
}

suseconds_t	get_time(t_philo *p, int i)
{
	suseconds_t	ms;
	time_t		sec;

	gettimeofday(&p->data->time[i].time_now, NULL);
	if (p->data->time_from_start.tv_sec == p->data->time[i].time_now.tv_sec)
	{
		ms = (p->data->time[i].time_now.tv_usec
				- p->data->time_from_start.tv_usec) / 1000;
	}
	else
	{
		sec = p->data->time[i].time_now.tv_sec - p->data->time_from_start.tv_sec;
		ms = (sec * 1000) + ((p->data->time[i].time_now.tv_usec
					- p->data->time_from_start.tv_usec) / 1000);
	}
	return (ms);
}

int	do_something(char something, t_philo *p)
{
	pthread_mutex_lock(p->data->message_queue);
	if (*p->data->death == 1)
	{
		pthread_mutex_unlock(p->data->message_queue);
		return (0);
	}
	p->data->time[*p->philo_id - 1].time_in_ms = get_time(p, *p->philo_id - 1);
	if (something == 'f')
		printf("%ld %d has taken a fork\n", p->data->time[*p->philo_id - 1].time_in_ms, *p->philo_id);
	else if (something == 'e')
		printf("%ld %d is eating\n", p->data->time[*p->philo_id - 1].time_in_ms, *p->philo_id);
	else if (something == 's')
		printf("%ld %d is sleeping\n", p->data->time[*p->philo_id - 1].time_in_ms, *p->philo_id);
	else if (something == 't')
		printf("%ld %d is thinking\n", p->data->time[*p->philo_id - 1].time_in_ms, *p->philo_id);
	else if (something == 'd')
		printf("%ld %d died\n", p->data->time[*p->philo_id - 1].time_in_ms, *p->philo_id);
	pthread_mutex_unlock(p->data->message_queue);
	return (1);
}
