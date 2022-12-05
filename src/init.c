/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:40:54 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/05 18:24:18 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	free_philo(t_philo *p)
{
	// free(p->data);
	free(p->philo_id);
	// p->data = NULL;
	p->philo_id = NULL;
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

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_philo)
	{
		data->p[i].data = malloc(sizeof(t_data));
		data->p[i].philo_id = malloc(sizeof(int));
		if (data->p[i].philo_id == NULL || data->p[i].data == NULL)
		{
			free(data->p[i].data);
			free(data->p[i].philo_id);
			data->p[i].data = NULL;
			data->p[i].philo_id = NULL;
			return (0);
		}
		data->p[i].data = data;
		*data->p[i].philo_id = i + 1;
		data->p[i].left_fork = &data->forks_id[i];
		if (i + 1 < data->args.n_philo)
			data->p[i].right_fork = &data->forks_id[i + 1];
		else
			data->p[i].right_fork = &data->forks_id[0];
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
		return (0);
	data->i = 0;
	while (data->i < data->args.n_philo)
	{
		pthread_mutex_init(&data->forks_id[data->i], NULL);
		data->i++;
	}
	*data->stop = 0;
	data->i = 0;
	if (!philo_init(data))
		return (0);
	return (1);
}
