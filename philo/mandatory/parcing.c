/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:04:29 by messkely          #+#    #+#             */
/*   Updated: 2024/09/09 10:22:58 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' && str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + (str[i++] - 48);
		if ((res * sign) < -2147483648 && (res * sign) > 2147483647)
			return (2147483649);
	}
	return (sign * res);
}

int	is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '0' || !*s)
		return (0);
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
}

int	check_args_is_valid(char **av)
{
	if (!is_num(av[1]) || ft_atoi(av[1]) > PHILO_MAX)
		return (ft_error("Invalid philosophers number\n"), 1);
	if (!is_num(av[2]))
		return (ft_error("Invalid time to die\n"), 1);
	if (!is_num(av[3]))
		return (ft_error("Invalid time to eat\n"), 1);
	if (!is_num(av[4]))
		return (ft_error("Invalid time to sleep\n"), 1);
	if (av[5] && (!is_num(av[5]) || ft_atoi(av[5]) > 2147483647))
		return (ft_error("Invalid number of times each philosopher must eat\n"), 1);
	return (0);
}
