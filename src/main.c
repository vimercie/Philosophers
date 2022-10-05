/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:31:44 by vimercie          #+#    #+#             */
/*   Updated: 2022/10/05 19:28:54 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
	pthread_t	thread_philos;
	t_philo 	p;
	int 		i;

	i = 0;
	p.n_philo = argv[1];
	p.t_die = argv[2];
	p.t_eat = argv[3];
	p.t_sleep = argv[4];
	if (argc == 6)
		p.n_eat == argv[5];
	while (i < p.n_philo)
	{
		pthread_create("We'll be back soon");
	}
}
