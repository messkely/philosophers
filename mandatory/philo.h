/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:59:20 by messkely          #+#    #+#             */
/*   Updated: 2024/05/27 15:44:30 by messkely         ###   ########.fr       */
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

typedef struct s_philo
{
	size_t	start_time;
	size_t	sleep_time;
	size_t	eat_time;
	size_t	die_time;
	int		philo_num;
	int		left_fork;
	int		rigth_fork;
}	t_philo;

void	ft_error(char *str);
int		is_num(char *s);
void	check_args_is_valid(char **av);
void	init_table(t_philo *philos);

#endif