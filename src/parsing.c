/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:24:17 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/15 09:28:27 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	arg_check(int argc)
{
	if (argc < 5 || argc > 6)
	{
		if (argc == 1)
		{
			write(2, "Usage : ./philo [number_of_philosophers]", 40);
			write(2, " [time_to_die] [time_to_eat] [time_to_sleep]", 44);
			write(2, " [number_of_times_each_philosopher_must_eat]\n", 45);
		}
		else
			write(2, "invalid number of argument\n", 27);
		return (0);
	}
	return (1);
}

int	print_error(int errnum, char *arg)
{
	if (errnum == 1)
	{
		write(2, arg, ft_strlen(arg));
		write(2, " value can't be 0\n", 18);
	}
	else if (errnum == 2)
		write(2, "all arguments must be integers\n", 31);
	else if (errnum == 3)
		write(2, "argument value can't be negative\n", 33);
	else if (errnum == 4)
		write(2, "there must be at least one philosopher\n", 39);
	return (0);
}

int	args_init(t_data *data, int argc, char *argv[])
{
	int	return_val;

	return_val = 1;
	data->args.n_philo = ft_atoi(argv[1]);
	data->args.t_die = ft_atoi(argv[2]);
	if (data->args.t_die == 0)
		return_val = print_error(1, "t_die");
	data->args.t_eat = ft_atoi(argv[3]);
	if (data->args.t_eat == 0)
		return_val = print_error(1, "t_eat");
	data->args.t_sleep = ft_atoi(argv[4]);
	if (data->args.t_sleep == 0)
		return_val = print_error(1, "t_sleep");
	if (argc == 6)
		data->args.n_eat = ft_atoi(argv[5]);
	else
		data->args.n_eat = 0;
	return (return_val);
}

int	parsing(t_data *data, int argc, char *argv[])
{
	int	return_val;

	return_val = 1;
	data->args.argc = argc;
	if (!arg_check(argc))
		return (0);
	else if (!is_integer(argv) || !is_signed_int(argv))
		return (print_error(2, NULL));
	if (!args_init(data, argc, argv))
		return_val = 0;
	if (is_negative(data))
		return_val = print_error(3, NULL);
	if (data->args.n_philo < 1)
		return_val = print_error(4, NULL);
	return (return_val);
}
