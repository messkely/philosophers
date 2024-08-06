/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:37:48 by messkely          #+#    #+#             */
/*   Updated: 2024/08/05 13:43:06 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(t_philo *philo, char **av)
{
	
	philo->dead_flag = 0;
	philo->philo_num = ft_atoi(av[1]);
	philo->die_time = ft_atoi(av[2]);
	philo->eat_time = ft_atoi(av[3]);
	philo->sleep_time = ft_atoi(av[4]);
	if (av[5])
		philo->num_times_to_eat = ft_atoi(av[5]);
	else
		philo->num_times_to_eat = -1;
	printf("hi\n");
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;
	
	i = 0;
	while (i < philo_num)
		pthread_mutex_init(&forks[i++], NULL);
}

void	init_philosophers(t_philo *philos, pthread_mutex_t *forks)
{
	int	i;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;

	i = 0;
	pthread_mutex_init(&write_lock, NULL);
	pthread_mutex_init(&meal_lock, NULL);
	pthread_mutex_init(&death_lock, NULL);
	while (i < philos->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].state = THINKING;
		philos[i].start_time = get_current_time();
		philos[i].write_lock = &write_lock;
		philos[i].meal_lock = &meal_lock;
		philos[i].death_lock = &death_lock;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].philo_num - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_table(t_philo *philos, pthread_mutex_t *forks, char **av)
{
	init_program(philos, av);
	init_forks(forks, philos->philo_num);
	init_philosophers(philos, forks);
}
