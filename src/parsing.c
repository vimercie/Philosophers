/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:24:17 by vimercie          #+#    #+#             */
/*   Updated: 2022/11/04 16:08:38 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	parsing(t_data *data, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		write(1, "invalid number of argument\n", 27);
		return (0);
	}
	if (argc == 5)
		data->n_eat = 0;
	else
	{
		if (is_number(argv[5]))
			data->n_eat = ft_atoi(argv[5]);
		else
		{
			write(1, "all arguments must be integers\n", 31);
			return (0);
		}
	}
	if (!is_number(argv[1])
		|| !is_number(argv[2])
		|| !is_number(argv[3])
		|| !is_number(argv[4]))
	{
		write(1, "all arguments must be integers\n", 31);
		return (0);
	}
	data->n_philo = ft_atoi(argv[1]);
	if (data->n_philo < 1)
	{
		write(1, "there must be at least one philosopher\n", 39);
		return (0);
	}
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (data->n_philo < 0
		|| data->t_die < 0
		|| data->t_eat < 0
		|| data->t_sleep < 0)
	{
		write(1, "argument value can't be negative\n", 33);
		return (0);
	}
	return (1);
}
