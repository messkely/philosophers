/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:04:29 by messkely          #+#    #+#             */
/*   Updated: 2024/08/04 10:36:06 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *s)
{
	int i;

	i = 0;
	if (s[i] == '-' || s[i] == '0')
		return (0);
	while (ft_isdigit(s[i]))
		i++;
	return (1);
}

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}

void	check_args_is_valid(char **av)
{
	if (!is_num(av[1]) || ft_atoi(av[1]) > PHILO_MAX)
		ft_error("Invalid philosophers number\n");
	if (!is_num(av[2]))
		ft_error("Invalid time to die\n");
	if (!is_num(av[3]))
		ft_error("Invalid time to eat\n");
	if (!is_num(av[4]))
		ft_error("Invalid time to sleep\n");
	if (av[5] && !is_num(av[5]))
		ft_error("Invalid number of times each philosopher must eat\n");
}
