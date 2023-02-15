/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:09:29 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/15 11:07:48 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_sated(t_philo *p)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&p->n_eat_lock);
	if (p->n_eat > 0)
	{
		p->n_eat--;
		if (p->n_eat == 0)
			ret = 1;
	}
	pthread_mutex_unlock(&p->n_eat_lock);
	return (ret);
}

int	is_stop(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->stop_lock);
	ret = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (ret);
}

int	check_satiety(t_data *data)
{
	int	n_hungry_philo;
	int	i;

	i = 0;
	n_hungry_philo = data->args.n_philo;
	while (i < data->args.n_philo)
	{
		pthread_mutex_lock(&data->p[i].n_eat_lock);
		if (data->p[i].n_eat == 0)
			n_hungry_philo--;
		pthread_mutex_unlock(&data->p[i].n_eat_lock);
		i++;
	}
	if (n_hungry_philo == 0)
		return (1);
	return (0);
}

int	check_death(t_data *data, int i)
{
	suseconds_t	since_last_meal;

	pthread_mutex_lock(&data->last_meal_lock);
	since_last_meal = get_time(data) - data->p[i].last_meal;
	pthread_mutex_unlock(&data->last_meal_lock);
	if (since_last_meal >= data->args.t_die)
		return (1);
	return (0);
}

int	check_stop(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		if (check_satiety(data))
			break ;
		if (check_death(data, i))
		{
			do_something('d', &data->p[i]);
			break ;
		}
		i++;
	}
	pthread_mutex_lock(&data->stop_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_lock);
	return (1);
}
