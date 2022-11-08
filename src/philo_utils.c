/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:34:57 by vimercie          #+#    #+#             */
/*   Updated: 2022/11/08 19:14:33 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	get_time(t_philo *p)
{
	suseconds_t	n;

	gettimeofday(&p->time_now, NULL);
	n = (p->time_now.tv_usec - p->time_from_start->tv_usec) / 1000;
	return (n);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	is_negative;

	i = 0;
	res = 0;
	is_negative = 1;
	if (!str[0])
		return (0);
	if (str[0] == '-')
	{
		is_negative *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * is_negative);
}
