/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:31:34 by vimercie          #+#    #+#             */
/*   Updated: 2022/10/05 18:31:34 by vimercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				*philo_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}				t_philo;

typedef struct s_data
{
	pthread_t		*threads;
	t_philo			*p;
	pthread_mutex_t	*forks_id;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
}				t_data;

// parsing
int	parsing(t_data *p, int argc, char *argv[]);

// threading
int	thread_init(t_data *p);

// init
int	data_init(t_data *data);
int	philo_init(t_data *data, int i);

// utils
int	ft_isdigit(int c);
int	is_number(char *s);
int	ft_atoi(const char *str);

#endif