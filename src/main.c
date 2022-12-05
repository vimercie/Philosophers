/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:31:44 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/05 19:24:09 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!parsing(&data, argc, argv))
		return (0);
	if (!data_init(&data))
		return (0);
	if (!thread_init(&data))
		free_data(&data);
	data.i = 0;
	while (data.i < data.args.n_philo)
	{
		free_philo(&data.p[data.i]);
		data.i++;
	}
	free_data(&data);
	return (0);
}
