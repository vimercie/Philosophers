/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:40:54 by vimercie          #+#    #+#             */
/*   Updated: 2022/11/04 16:10:41 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_init(t_data *data, int i)
{
		data->p[i].philo_id = malloc(sizeof(int));
		if (data->p[i].philo_id == NULL)
		{
			free(data->p[i].philo_id);
			return (0);
		}
		*data->p[i].philo_id = i + 1;
		data->p[i].right_fork = &data->forks_id[i];
		if (i != 0)
			data->p[i].left_fork = &data->forks_id[i - 1];
		else
			data->p[i].left_fork = &data->forks_id[data->n_philo - 1];
		return (1);
}

int	data_init(t_data *data)
{
	data->threads = malloc(data->n_philo * sizeof(pthread_t));
	data->p = malloc(data->n_philo * sizeof(t_philo));
	data->forks_id = malloc(data->n_philo * sizeof(pthread_mutex_t));
	if (data->threads == NULL || data->p == NULL || data->forks_id == NULL)
	{
		free(data->threads);
		free(data->forks_id);
		free(data->p);
		return (0);
	}
	return (1);
}
