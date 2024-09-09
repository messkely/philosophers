/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:59:20 by messkely          #+#    #+#             */
/*   Updated: 2024/09/09 10:22:41 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define PHILO_MAX 230

typedef struct s_info
{
	int				total_eat;
	int				death;
	pthread_mutex_t	total_eat_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	death_lock;
}	t_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	size_t			start_time;
	size_t			sleep_time;
	size_t			eat_time;
	size_t			die_time;
	size_t			last_meal;
	int				philo_num;
	int				num_times_to_eat;
	int				eating_counter;
	int				*death;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_info			*info;
}	t_philo;

int		check_args_is_valid(char **av);
void	init_table(t_info *init, t_philo *philos,
			pthread_mutex_t *forks, char **av);
int		dinner_start(t_philo *philo, pthread_mutex_t *forks);
int		is_dead(t_philo *philo);
long	ft_atoi(const char *str);
int		ft_strlen(char *str);
void	ft_usleep(size_t milliseconds, t_philo *philo);
size_t	get_current_time(void);
void	print_msg(char *str, t_philo *philo, int id);
void	destroy_mutexes(int option, pthread_mutex_t *forks,
			t_philo *philo, int n);

#endif
//  +212 6 01 84 99 22