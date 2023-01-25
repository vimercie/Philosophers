/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:31:44 by vimercie          #+#    #+#             */
/*   Updated: 2023/01/24 18:35:45 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	free_data(t_data *data)
{
	free(data->p);
	free(data->forks_id);
	data->p = NULL;
	data->forks_id = NULL;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!parsing(&data, argc, argv))
		return (0);
	if (!data_init(&data))
		return (0);
	threading(&data);
	free_data(&data);
	return (0);
}
