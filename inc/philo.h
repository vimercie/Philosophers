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
	struct timeval	*time_from_start;
	struct timeval	time_now;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
}				t_philo;

typedef struct s_data
{
	pthread_t		*threads;
	t_philo			*p;
	pthread_mutex_t	*forks_id;
	struct timeval	time_from_start;
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
int	custom_usleep(int time_in_ms, t_philo *p);
int	get_time(t_philo *p);
int	ft_isdigit(int c);
int	is_number(char *s);
int	ft_atoi(const char *str);

#endif