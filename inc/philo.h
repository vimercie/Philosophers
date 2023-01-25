/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:26:43 by vimercie          #+#    #+#             */
/*   Updated: 2022/12/05 18:26:43 by vimercie         ###   ########lyon.fr   */
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
# include <stdbool.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_args	t_args;

typedef struct s_args
{
	int	argc;
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
}				t_args;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				id;
	int				n_eat;
	suseconds_t		last_meal;
}				t_philo;

typedef struct s_data
{
	t_philo			*p;
	t_args			args;
	pthread_mutex_t	*forks_id;
	struct timeval	time_from_start;
	struct timeval	time_now;
	bool			death;
	pthread_mutex_t	message_queue;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
}				t_data;

// parsing
int	parsing(t_data *p, int argc, char *argv[]);
int	args_init(t_data *data, int argc, char *argv[]);
int	arg_check(int argc);

// threading
int	threading(t_data *p);
int	do_something(char something, t_philo *p);
int	exit_philo(t_data *data);

// init
int	data_init(t_data *data);
int	philo_init(t_data *data);

// utils
int	check_death(t_data *data);
suseconds_t	get_time(t_data *data);
int	custom_usleep(int t_ms, t_philo *p);
int	eat_pasta(t_philo *p);
int	do_something(char something, t_philo *p);

// checking
int	is_dead(t_data *data);
int	is_signed_int(char *argv[]);
int	is_integer(char *argv[]);
int	is_number(char *s);
int	is_negative(t_data *data);

// libft
int	ft_strlen(const char *s);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

// free
int	free_data(t_data *data);

#endif