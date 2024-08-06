/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_procces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:54:59 by messkely          #+#    #+#             */
/*   Updated: 2024/08/06 12:50:40 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (philo->dead_flag) // you was removing the the pointer symbol.
		return (pthread_mutex_unlock(philo->death_lock), 1);
	return (pthread_mutex_unlock(philo->death_lock), 0);
}

void	is_think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	is_eat(t_philo *philo)
{
	pthread_mutex_lock()
}

void	*philo_procces(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->eat_time);
	while (!is_dead(philo))
		(is_eat(philo), is_sleep(philo), is_think(philo));
	return (arg);
}

void	philos_procces(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_num)
		(pthread_create(philo[i].thread, NULL, philo_procces, &philo[i]), i++);
	i = 0;
	while (i < philo->philo_num)
		pthread_join(philo[i++].thread, NULL);
}
