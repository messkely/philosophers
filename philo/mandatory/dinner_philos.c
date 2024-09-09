/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:56:17 by messkely          #+#    #+#             */
/*   Updated: 2024/09/07 16:48:38 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_lock);
	*philo->death = 1;
	pthread_mutex_unlock(&philo->info->death_lock);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_msg("has taken a fork", philo, philo->id);
	if (philo->philo_num == 1)
	{
		ft_usleep(philo->die_time, philo);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_msg("has taken a fork", philo, philo->id);
	print_msg("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->info->meal_lock);
	philo->last_meal = get_current_time();
	philo->eating_counter++;
	if (philo->eating_counter == philo->num_times_to_eat)
	{
		pthread_mutex_lock(&philo->info->total_eat_lock);
		philo->info->total_eat++;
		pthread_mutex_unlock(&philo->info->total_eat_lock);
	}
	pthread_mutex_unlock(&philo->info->meal_lock);
	ft_usleep(philo->eat_time, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*philo_procces(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (!is_dead(philo))
	{
		eat(philo);
		print_msg("is sleeping", philo, philo->id);
		ft_usleep(philo->sleep_time, philo);
		print_msg("is thinking", philo, philo->id);
	}
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo[0].philo_num)
		{
			pthread_mutex_lock(&philo->info->meal_lock);
			if (philo->info->total_eat == philo[0].philo_num)
			{
				dead(philo);
				return (pthread_mutex_unlock(&philo->info->meal_lock), NULL);
			}
			if (get_current_time() - philo[i].last_meal >= philo[i].die_time)
			{
				(print_msg("died", philo + i, philo[i].id), dead(philo + i));
				return (pthread_mutex_unlock(&philo->info->meal_lock), NULL);
			}
			pthread_mutex_unlock(&philo->info->meal_lock);
			i++;
		}
	}
	return (NULL);
}

int	dinner_start(t_philo *philo, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, philo) != 0)
		return (destroy_mutexes(1, forks, philo, philo[0].philo_num), 1);
	while (i < philo[0].philo_num)
	{
		if (pthread_create(&philo[i].thread, NULL,
				&philo_procces, &philo[i]) != 0)
			return (destroy_mutexes(1, forks, philo, philo[0].philo_num), 1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (destroy_mutexes(2, forks, philo, philo[0].philo_num), 1);
	i = 0;
	while (i < philo[0].philo_num)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (destroy_mutexes(2, forks, philo, philo[0].philo_num), 1);
		i++;
	}
	return (0);
}
