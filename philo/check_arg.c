/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:58:14 by mjlem             #+#    #+#             */
/*   Updated: 2022/06/07 15:19:07 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	init_values(t_args **args, char **av)
{
	int	i;

	i = 0;
	(*args)->ph_num = ft_atoi(av[1]);
	(*args)->t_die = ft_atoi(av[2]);
	(*args)->t_eat = ft_atoi(av[3]);
	(*args)->t_sleep = ft_atoi(av[4]);
	if (av[5])
		(*args)->num_eat = ft_atoi(av[5]);
	else
		(*args)->num_eat = -1;
	(*args)->fork = malloc (sizeof(pthread_mutex_t) * (*args)->ph_num);
	while (i < (*args)->ph_num)
	{
		if (pthread_mutex_init(&(*args)->fork[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&(*args)->print, NULL);
	return (0);
}

t_philo	*init_my_data(t_philo *data, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->ph_num)
	{
		data[i].id = i + 1;
		data[i].args = args;
		data[i].last_meal = args->time_start;
		data[i].meal_count = args->num_eat;
		data[i].is_eating = 1;
		i++;
	}
	return (data);
}
