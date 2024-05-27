/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:04:29 by messkely          #+#    #+#             */
/*   Updated: 2024/05/27 15:25:36 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' && s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}

void	check_args_is_valid(char **av)
{
	if (!is_num(av[1]) || ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0)
		ft_error("Invalid philosophers number\n");
	if (!is_num(av[2]) || ft_atoi(av[2]) <= 0)
		ft_error("Invalid time to die\n");
	if (!is_num(av[3]) || ft_atoi(av[3]) <= 0)
		ft_error("Invalid time to eat\n");
	if (!is_num(av[4]) || ft_atoi(av[4]) <= 0)
		ft_error("Invalid time to sleep\n");
	if (av[5] && (!is_num(av[5]) || ft_atoi(av[5]) <= 0))
		ft_error("Invalid number of times each philosopher must eat\n");
}
