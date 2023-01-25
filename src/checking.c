/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:19:27 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/25 03:55:54 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->death == 1)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}

int	is_signed_int(char *argv[])
{
	int	i;
	int	size;

	i = 1;
	while (argv[i])
	{
		size = ft_strlen(argv[i]);
		if (argv[i][0] != '-')
		{
			if (size > 10
				|| (size == 10 && ft_strcmp(argv[i], "2147483647") > 0))
				return (0);
		}
		else
		{
			if (size > 11
				|| (size == 11 && ft_strcmp(argv[i], "-2147483648") > 0))
				return (0);
		}
		i++;
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
			return (0);
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
	if (s[0] == '-' && s[1])
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
		return (1);
	return (0);
}
