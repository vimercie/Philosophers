/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:31:44 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/14 17:47:13 by vimercie         ###   ########.fr       */
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
	free(data->time);
	free(data->death);
	data->p = NULL;
	data->threads = NULL;
	data->forks_id = NULL;
	data->time = NULL;
	data->death = NULL;
	return (0);
}

int	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.n_philo)
	{
		free_philo(&data->p[i]);
		i++;
	}
	free_data(data);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!parsing(&data, argc, argv))
		return (0);
	if (!data_init(&data))
		return (0);
	if (!threading(&data))
		free_data(&data);
	free_all(&data);
	return (0);
}
