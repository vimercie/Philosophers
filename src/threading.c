/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:32:31 by vimercie          #+#    #+#             */
/*   Updated: 2022/11/18 21:08:01 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_dead(t_philo *p)
{
	p->time_in_ms = get_time(p);
	if (p->time_in_ms - p->end_of_meal >= p->t_die)
	{
		printf("%ld %d DIED !\n", p->time_in_ms, *p->philo_id);
		*p->data->stop = 1;
		return (1);
	}
	return (0);
}

int	do_something(char something, t_philo *p)
{
	p->time_in_ms = get_time(p);
	*p->thinking = 0;
	if (*p->data->stop == 1)
		return (0);
	if (something == 'f')
		printf("%ld %d has taken a fork\n", p->time_in_ms, *p->philo_id);
	else if (something == 'e')
	{
		printf("%ld %d is eating\n", p->time_in_ms, *p->philo_id);
		if (!custom_usleep(p->t_eat, p))
			return (0);	
	}
	else if (something == 's')
	{
		printf("%ld %d is sleeping\n", p->time_in_ms, *p->philo_id);
		if (!custom_usleep(p->t_sleep, p))
			return (0);
	}
	else if (something == 't')
	{
		printf("%ld %d is thinking\n", p->time_in_ms, *p->philo_id);
		*p->thinking = 1;
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo		*p;
	int			n_meal;
	int			laps;

	p = (t_philo *)arg;
	p->time_in_ms = get_time(p);
	p->end_of_meal = 0;
	n_meal = 0;
	laps = 1;
	while (1)
	{
		while (*p->thinking == 1)
		{
			custom_usleep(10, p);
			if (*p->data->stop == 1)
				return (0);
			if (is_dead(p))
				return (0);
		}
		if (*p->data->stop == 1)
			return (0);
		if (n_meal <= laps + 1)
		{
			if (*p->data->stop == 1)
				return (0);
			pthread_mutex_lock(p->right_fork);
			if (p->right_fork == p->left_fork)
				break ;
			do_something('f', p);
			pthread_mutex_lock(p->left_fork);
			do_something('f', p);
			do_something('e', p);
			n_meal++;
			pthread_mutex_unlock(p->right_fork);
			pthread_mutex_unlock(p->left_fork);
			p->time_in_ms = get_time(p);
			p->end_of_meal = p->time_in_ms;
			do_something('s', p);
			do_something('t', p);
		}
		if (p->right_fork == p->left_fork)
			pthread_mutex_unlock(p->right_fork);
		if (is_dead(p))
			return (0);
		laps++;
	}
	free(p->philo_id);
	return (0);
}

int	thread_init(t_data *data)
{
	int	i;

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
