/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:40:54 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/25 04:12:59 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	fork_init(t_data *data, int i)
{
	data->p[i].left_fork = &data->forks_id[i];
	if (pthread_mutex_init(data->p[i].left_fork, NULL) != 0)
		return (0);
	if (data->args.n_philo > 1)
	{
		if (i < data->args.n_philo - 1)
		{
			data->p[i].right_fork = &data->forks_id[i + 1];
			if (pthread_mutex_init(data->p[i].right_fork, NULL) != 0)
				return (0);
		}
		else
		{
			data->p[i].right_fork = &data->forks_id[0];
			if (pthread_mutex_init(data->p[i].right_fork, NULL) != 0)
				return (0);
		}
	}
	else
		data->p[i].right_fork = NULL;
	return (1);
}

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_philo)
	{
		if (!fork_init(data, i))
			return (0);
		data->p[i].data = data;
		data->p[i].id = i + 1;
		data->p[i].last_meal = 0;
		if (data->args.argc == 6)
			data->p[i].n_eat = data->args.n_eat;
		else
			data->p[i].n_eat = -1;
		i++;
	}
	return (1);
}

int	data_init(t_data *data)
{
	data->p = malloc(data->args.n_philo * sizeof(t_philo));
	data->forks_id = malloc(data->args.n_philo * sizeof(pthread_mutex_t));
	if (data->p == NULL
		|| data->forks_id == NULL)
	{
		free_data(data);
		return (0);
	}
	pthread_mutex_init(&data->message_queue, NULL);
	pthread_mutex_init(&data->time_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	data->death = 0;
	if (!philo_init(data))
	{
		free_data(data);
		return (0);
	}
	gettimeofday(&data->time_from_start, NULL);
	return (1);
}
