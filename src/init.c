/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:40:54 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/12 01:53:43 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	free_philo(t_philo *p)
{
	free(p->philo_id);
	free(p->n_eat);
	p->philo_id = NULL;
	p->n_eat = NULL;
	return (0);
}

int	free_data(t_data *data)
{
	free(data->p);
	free(data->threads);
	free(data->forks_id);
	free(data->stop);
	data->p = NULL;
	data->threads = NULL;
	data->forks_id = NULL;
	data->stop = NULL;
	return (0);
}

int	fork_init(t_data *data, int i)
{
		data->p[i].left_fork = &data->forks_id[i];
		if (pthread_mutex_init(&data->forks_id[i], NULL) != 0)
			return (0);
		if (data->args.n_philo > 1)
		{
			if (i < data->args.n_philo - 1)
			{
				data->p[i].right_fork = &data->forks_id[i + 1];
				if (pthread_mutex_init(&data->forks_id[i + 1], NULL) != 0)
					return (0);
			}
			else
			{
				data->p[i].right_fork = &data->forks_id[0];
				if (pthread_mutex_init(&data->forks_id[0], NULL) != 0)
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
		data->p[i].philo_id = malloc(sizeof(int));
		data->p[i].n_eat = malloc(sizeof(int));
		if (data->p[i].philo_id == NULL
			|| data->p[i].n_eat == NULL)
			{
				free_philo(&data->p[i]);
				return (0);
			}
		data->p[i].data = data;
		*data->p[i].philo_id = i + 1;
		*data->p[i].n_eat = data->args.n_eat;
		data->p[i].time.time_from_start = &data->time_from_start;
		gettimeofday(&data->p[i].time.time_now, NULL);
		i++;
	}
	return (1);
}

int	data_init(t_data *data)
{
	data->p = malloc(data->args.n_philo * sizeof(t_philo));
	data->threads = malloc(data->args.n_philo * sizeof(pthread_t));
	data->forks_id = malloc(data->args.n_philo * sizeof(pthread_mutex_t));
	data->stop = malloc(sizeof(int));
	if (data->p == NULL
		|| data->threads == NULL
		|| data->forks_id == NULL
		|| data->stop == NULL)
	{
		free_data(data);
		return (0);
	}
	data->i = 0;
	*data->stop = 0;
	gettimeofday(&data->time_from_start, NULL);
	if (!philo_init(data))
	{
		free_data(data);
		return (0);
	}
	return (1);
}
