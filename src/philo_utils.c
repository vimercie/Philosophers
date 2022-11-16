/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:34:57 by vimercie          #+#    #+#             */
/*   Updated: 2022/11/16 13:06:20 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	custom_usleep(int time_in_ms, t_philo *p)
{
	int	start;
	int	now;

	start = get_time(p);
	now = 0;
	while ((now - start) < time_in_ms)
	{
		usleep(50);
		now = get_time(p);
	}
	return (1);
}

int	get_time(t_philo *p)
{
	suseconds_t	n;
	time_t		sec;

	gettimeofday(&p->time_now, NULL);
	if (p->time_from_start->tv_sec == p->time_now.tv_sec)
		n = (p->time_now.tv_usec - p->time_from_start->tv_usec) / 1000;
	else
	{
		sec = p->time_now.tv_sec - p->time_from_start->tv_sec;
		n = (sec * 1000) + ((p->time_now.tv_usec - p->time_from_start->tv_usec) / 1000);
	}
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
