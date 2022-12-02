/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:31:44 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/02 05:20:06 by vimercie         ###   ########.fr       */
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
	return (0);
}
