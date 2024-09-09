/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:03:55 by messkely          #+#    #+#             */
/*   Updated: 2024/09/09 10:22:17 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print_msg(char *msg, t_philo *philo, int id)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(&philo->info->write_lock);
	if (!is_dead(philo))
		printf("%zu %d %s\n", time, id, msg);
	pthread_mutex_unlock(&philo->info->write_lock);
}

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->info->death_lock);
	dead = *philo->death;
	pthread_mutex_unlock(&philo->info->death_lock);
	return (dead);
}

void	destroy_mutexes(int option, pthread_mutex_t *forks,
		t_philo *philo, int n)
{
	int	i;

	i = 0;
	if (option == 1)
		write(2, "error of creating the tread\n", 28);
	else if (option == 2)
		write(2, "error of join the thread\n", 25);
	while (i < n)
		pthread_mutex_destroy(&forks[i++]);
	if (0 != pthread_mutex_destroy(&philo->info->total_eat_lock))
		write(2, "error\n", 6);
	if (0 != pthread_mutex_destroy(&philo->info->write_lock))
		write(2, "error\n", 6);
	if (0 != pthread_mutex_destroy(&philo->info->meal_lock))
		write(2, "error\n", 6);
	if (0 != pthread_mutex_destroy(&philo->info->death_lock))
		write(2, "error\n", 6);
}

int	main(int ac, char **av)
{
	t_info			info;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (check_args_is_valid(av))
		return (1);
	init_table(&info, philos, forks, av);
	dinner_start(philos, forks);
	return (destroy_mutexes(0, forks, philos, philos[0].philo_num), 0);
}
