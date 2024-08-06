/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:59:20 by messkely          #+#    #+#             */
/*   Updated: 2024/08/06 11:35:18 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 400

enum
{
	// TAKEN_A_FORK,
	THINKING,
	EATING,
	SLEEPING
};

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				state;
	size_t			start_time;
	size_t			sleep_time;
	size_t			eat_time;
	size_t			die_time;
	int				philo_num;
	int				num_times_to_eat;
	int				dead_flag;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

void	ft_error(char *str);
int		is_num(char *s);
void	check_args_is_valid(char **av);
void	init_table(t_philo *philos, pthread_mutex_t *forks, char **av);
void	philos_procces(t_philo *philo);

long	ft_atoi(const char *str);
int		ft_strlen(char *str);
int		ft_isdigit(char c);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
void	print_message(char *str, t_philo *philo, int id);

#endif