/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:19:27 by vimercie          #+#    #+#             */
/*   Updated: 2023/02/15 10:01:43 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_stop(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->stop_lock);
	ret = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (ret);
}

int	is_signed_int(char *s)
{
	int	size;

	size = ft_strlen(s);
	if (s[0] != '-')
	{
		if (size > 10 || (size == 10 && ft_strcmp(s, "2147483647") > 0))
			return (0);
	}
	else
	{
		if (size > 11 || (size == 11 && ft_strcmp(s, "-2147483648") > 0))
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
		if (!is_number(argv[i]) || !is_signed_int(argv[i]))
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

int	is_allowed_val(t_data *data)
{
	int	return_val;
	
	return_val = 1;
	if (data->args.n_philo <= 0)
		return_val = print_error(1, "n_philo");
	if (data->args.t_die <= 0)
		return_val = print_error(1, "t_die");
	if (data->args.t_eat <= 0)
		return_val = print_error(1, "t_eat");
	if (data->args.t_sleep <= 0)
		return_val = print_error(1, "t_sleep");
	if (data->args.n_eat <= 0 && data->args.argc == 6)
		return_val = print_error(1, "n_eat");
	return (return_val);
}
