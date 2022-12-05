/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:19:27 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/05 16:16:35 by vimercie         ###   ########lyon.fr   */
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

int	is_integer(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]))
		{
			write(1, "all arguments must be integers\n", 31);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_number(char *s)
{
	int	i;

	i = 0;
	if (!s[0])
		return (0);
	if (s[0] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_negative(t_data *data)
{
	if (data->args.n_philo < 0
		|| data->args.t_die < 0
		|| data->args.t_eat < 0
		|| data->args.t_sleep < 0
		|| data->args.n_eat < 0)
	{
		write(1, "argument value can't be negative\n", 33);
		return (0);
	}
	return (1);
}

int	n_eat_init(int argc, char *argv[], t_data *data)
{
	if (argc == 5)
		data->args.n_eat = 0;
	else
	{
		if (is_number(argv[5]))
			data->args.n_eat = ft_atoi(argv[5]);
		else
		{
			write(1, "all arguments must be integers\n", 31);
			return (0);
		}
	}
	return (1);
}
