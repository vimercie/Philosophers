/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:40:54 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/02 07:00:16 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int free_philo(t_philo *p)
{
	// free(p->data);
	free(p->philo_id);
	// p->data = NULL;
	p->philo_id = NULL;
	return (0);
}

int free_data(t_data *data)
{
	free(data->p);
	free(data->threads);
	free(data->forks_id);
	free(data->stop);
	free(data->exit);
	data->p = NULL;
	data->threads = NULL;
	data->forks_id = NULL;
	data->stop = NULL;
	data->exit = NULL;
	return (0);
}

int philo_init(t_data *data, int i)
{
	data->p[i].data = malloc(sizeof(t_data));
	data->p[i].philo_id = malloc(sizeof(int));
	if (data->p[i].philo_id == NULL || data->p[i].data == NULL)
	{
		dprintf(1, "relou\n");
		free(data->p[i].data);
		free(data->p[i].philo_id);
		data->p[i].data = NULL;
		data->p[i].philo_id = NULL;
		return (0);
	}
	data->p[i].data = data;
	*data->p[i].philo_id = i + 1;
	data->p[i].right_fork = &data->forks_id[i];
	if (i != 0)
		data->p[i].left_fork = &data->forks_id[i - 1];
	else
		data->p[i].left_fork = &data->forks_id[data->args.n_philo - 1];
	data->p[i].time.time_from_start = &data->time_from_start;
	gettimeofday(&data->p[i].time.time_now, NULL);
	return (1);
}

int data_init(t_data *data)
{
	data->p = malloc(data->args.n_philo * sizeof(t_philo));
	data->threads = malloc(data->args.n_philo * sizeof(pthread_t));
	data->forks_id = malloc(data->args.n_philo * sizeof(pthread_mutex_t));
	data->stop = malloc(sizeof(int));
	data->exit = malloc(sizeof(pthread_mutex_t));
	if (data->p == NULL
		|| data->threads == NULL
		|| data->forks_id == NULL
		|| data->stop == NULL
		|| data->exit == NULL)
		return (0);
	*data->stop = 0;
	data->i = 0;
	return (1);
}
