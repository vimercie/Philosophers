/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:24:17 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/24 19:16:13 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	arg_check(int argc)
{
	if (argc < 5 || argc > 6)
	{
		if (argc == 1)
		{
			write(1, "Usage : ./philo [number_of_philosophers]", 40);
			write(1, " [time_to_die] [time_to_eat] [time_to_sleep]", 44);
			write(1, " [number_of_times_each_philosopher_must_eat]\n", 45);
		}
		else
			write(1, "invalid number of argument\n", 27);
		return (0);
	}
	return (1);
}

int	args_init(t_data *data, int argc, char *argv[])
{
	int	error;

	error = 0;
	data->args.n_philo = ft_atoi(argv[1]);
	data->args.t_die = ft_atoi(argv[2]);
	if (data->args.t_die == 0)
	{
		write(1, "t_die value can't be 0\n", 23);
		error = 1;
	}
	data->args.t_eat = ft_atoi(argv[3]);
	if (data->args.t_eat == 0)
	{
		write(1, "t_eat value can't be 0\n", 23);
		error = 1;
	}
	data->args.t_sleep = ft_atoi(argv[4]);
	if (data->args.t_sleep == 0)
	{
		write(1, "t_sleep value can't be 0\n", 25);
		error = 1;
	}
	if (argc == 6)
		data->args.n_eat = ft_atoi(argv[5]);
	else
		data->args.n_eat = 0;
	if (error == 1)
		return (0);
	return (1);
}

int	parsing(t_data *data, int argc, char *argv[])
{
	int	error;

	error = 0;
	data->args.argc = argc;
	if (!arg_check(argc))
		return (0);
	else if (!is_integer(argv) || !is_signed_int(argv))
	{
		write(1, "all arguments must be integers\n", 31);
		return (0);
	}
	if (!args_init(data, argc, argv))
		error = 1;
	if (is_negative(data))
	{
		write(1, "argument value can't be negative\n", 33);
		error = 1;
	}
	if (data->args.n_philo < 1)
	{
		write(1, "there must be at least one philosopher\n", 39);
		error = 1;
	}
	if (error == 1)
		return (0);
	return (1);
}
