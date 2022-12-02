/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:24:17 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/02 03:30:54 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	parsing(t_data *data, int argc, char *argv[])
{
	if (!arg_check(argc)
		|| !is_integer(argv)
		|| !n_eat_init(argc, argv, data))
		return (0);
	data->args.n_philo = ft_atoi(argv[1]);
	data->args.t_die = ft_atoi(argv[2]);
	data->args.t_eat = ft_atoi(argv[3]);
	data->args.t_sleep = ft_atoi(argv[4]);
	if (data->args.n_philo < 1)
	{
		write(1, "there must be at least one philosopher\n", 39);
		return (0);
	}
	if (!is_negative(data))
		return (0);
	return (1);
}
