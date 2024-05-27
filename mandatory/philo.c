/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:03:55 by messkely          #+#    #+#             */
/*   Updated: 2024/05/27 15:36:37 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philos[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	check_args_is_valid(av);
	init_table(&philos);
	return (0);
}
