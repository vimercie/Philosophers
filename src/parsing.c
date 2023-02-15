/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:24:17 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/15 11:04:03 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_error(int errnum, char *arg)
{
	if (errnum == 1)
	{
		write(2, arg, ft_strlen(arg));
		write(2, " value can't be 0 or less\n", 26);
	}
	else if (errnum == 2)
		write(2, "all arguments must be integers\n", 31);
	return (0);
}

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

int	args_init(t_data *data, int argc, char *argv[])
{
	int	return_val;

	return_val = 1;
	data->args.n_philo = ft_atoi(argv[1]);
	data->args.t_die = ft_atoi(argv[2]);
	data->args.t_eat = ft_atoi(argv[3]);
	data->args.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->args.n_eat = ft_atoi(argv[5]);
	else
		data->args.n_eat = -1;
	return (return_val);
}

int	parsing(t_data *data, int argc, char *argv[])
{
	data->args.argc = argc;
	if (!arg_check(argc))
		return (0);
	if (!is_integer(argv))
		return (print_error(2, NULL));
	args_init(data, argc, argv);
	if (!is_allowed_val(data))
		return (0);
	return (1);
}
