/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 09:21:57 by mjlem             #+#    #+#             */
/*   Updated: 2022/06/10 09:23:10 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_time	my_time(void)
{
	t_time			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	my_sleep(t_time time)
{
	t_time	expected_time;
	t_time	temp_time;

	expected_time = my_time() + time;
	temp_time = my_time();
	while (temp_time < expected_time)
	{
		usleep(100);
		temp_time = my_time();
	}
}

int	is_zero(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] != '0')
		return (0);
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

int	check(char **av)
{
	int	i;

	i = 1;
	if (!av[i])
	{
		write(2, "Invalid argument\n", 17);
		return (0);
	}
	while (av[i])
	{
		if (is_zero(av[i]))
			i++;
		if (!av[i])
			break ;
		if (!ft_atoi(av[i]))
		{
			write(2, "Invalid argument\n", 16);
			return (0);
		}
		i++;
	}
	return (1);
}