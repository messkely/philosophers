/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:37:48 by messkely          #+#    #+#             */
/*   Updated: 2024/08/22 11:03:37 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < milliseconds)
	{
		if (is_dead(philo))
			break ;
		usleep(500);
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
		pthread_mutex_init(&forks[i++], NULL);
}

void	init_philosophers(t_philo *philos, pthread_mutex_t *forks, t_info *info)
{
	int	i;

	i = 0;
	while (i < philos->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].eating_counter = 0;
		philos[i].death = &info->death;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].philo_num - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		philos[i].info = info;
		i++;
	}
}

void	init_table(t_info *info, t_philo *philos,
	pthread_mutex_t *forks, char **av)
{
	int	i;

	info->total_eat = 0;
	info->death = 0;
	pthread_mutex_init(&info->total_eat_lock, NULL);
	pthread_mutex_init(&info->meal_lock, NULL);
	pthread_mutex_init(&info->write_lock, NULL);
	pthread_mutex_init(&info->death_lock, NULL);
	init_forks(forks, ft_atoi(av[1]));
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].philo_num = ft_atoi(av[1]);
		philos[i].die_time = ft_atoi(av[2]);
		philos[i].eat_time = ft_atoi(av[3]);
		philos[i].sleep_time = ft_atoi(av[4]);
		if (av[5])
			philos[i].num_times_to_eat = ft_atoi(av[5]);
		else
			philos[i].num_times_to_eat = -1;
		philos[i].info = info;
		i++;
	}
	init_philosophers(philos, forks, info);
}
