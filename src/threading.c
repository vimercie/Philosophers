/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:32:31 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/06 06:32:08 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	exit_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_philo)
	{
		pthread_join(data->p[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->args.n_philo)
	{
		pthread_mutex_destroy(&data->forks_id[i]);
		i++;
	}
	pthread_mutex_destroy(&data->message_queue);
	pthread_mutex_destroy(&data->time_lock);
	pthread_mutex_destroy(&data->n_eat_lock);
	pthread_mutex_destroy(&data->last_meal_lock);
	pthread_mutex_destroy(&data->stop_lock);
	return (1);
}

void	*one_philo(void *arg)
{
	t_philo			*p;

	p = (t_philo *)arg;
	if (p->n_eat == 0)
		return (0);
	pthread_mutex_lock(p->left_fork);
	do_something('f', p);
	while (1)
	{
		if (is_stop(p->data))
			break ;
	}
	pthread_mutex_unlock(p->left_fork);
	return (0);
}

void	*p_routine(void *arg)
{
	t_philo			*p;

	p = arg;
	if (p->n_eat == 0)
		return (0);
	if (p->id % 2 != 0)
	{
		do_something('t', p);
		custom_usleep(p->data->args.t_eat, p);
	}
	while (!is_stop(p->data))
	{
		take_forks(p);
		do_something('e', p);
		is_sated(p);
		custom_usleep(p->data->args.t_eat, p);
		do_something('s', p);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		custom_usleep(p->data->args.t_sleep, p);
		do_something('t', p);
	}
	return (0);
}

int	threading(t_data *data)
{
	int	i;

	i = 0;
	if (data->args.n_philo == 1)
	{
		pthread_create(&data->p[0].thread, NULL, &one_philo, &data->p[0]);
		check_stop(data);
	}
	else
	{
		while (i < data->args.n_philo)
		{
			pthread_create(&data->p[i].thread, NULL, &p_routine, &data->p[i]);
			i++;
		}
		check_stop(data);
	}
	exit_philo(data);
	return (1);
}
