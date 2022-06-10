/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:54:09 by mjlem             #+#    #+#             */
/*   Updated: 2022/06/07 15:19:26 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	my_time(void)
{
	t_time			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->args->fork[ph->id % ph->args->ph_num]);
	pthread_mutex_lock(&ph->args->print);
	printf("%lld %d has taken a fork\n",
		(my_time() - ph->args->time_start), ph->id);
	pthread_mutex_unlock(&ph->args->print);
	pthread_mutex_lock(&ph->args->fork[ph->id - 1]);
	pthread_mutex_lock(&ph->args->print);
	printf("%lld %d has taken a fork\n",
		(my_time() - ph->args->time_start), ph->id);
	pthread_mutex_unlock(&ph->args->print);
	pthread_mutex_lock(&ph->args->print);
	printf("%lld %d is eating\n",
		(my_time() - ph->args->time_start), ph->id);
	if (ph->meal_count > 0)
		ph->meal_count--;
	pthread_mutex_unlock(&ph->args->print);
	ph->last_meal = my_time();
	ph->is_eating = 0;
	my_sleep(ph->args->t_eat);
	ph->is_eating = 1;
	pthread_mutex_unlock(&ph->args->fork[ph->id - 1]);
	pthread_mutex_unlock(&ph->args->fork[ph->id % ph->args->ph_num]);
}

void	*routine(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (ph->id % 2)
		usleep(500);
	while (1)
	{
		eating(ph);
		pthread_mutex_lock(&ph->args->print);
		printf("%lld %d is sleeping\n",
			(my_time() - ph->args->time_start), ph->id);
		pthread_mutex_unlock(&ph->args->print);
		my_sleep(ph->args->t_sleep);
		pthread_mutex_lock(&ph->args->print);
		printf("%lld %d is thinking\n",
			(my_time() - ph->args->time_start), ph->id);
		pthread_mutex_unlock(&ph->args->print);
	}
	return (ph);
}

int	check_dead(t_args *args, t_philo *data)
{
	int	i;
	int	count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < args->ph_num)
		{
			if ((my_time() - data[i].last_meal > args->t_die)
				&& data[i].is_eating)
			{
				pthread_mutex_lock(&args->print);
				printf("%lld %d died\n",
					(my_time() - args->time_start), data[i].id);
				return (1);
			}
			count += data[i].meal_count;
			i++;
		}
		if (count == 0)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args		*args;
	pthread_t	*philo;
	t_philo		*data;
	int			i;

	i = 0;
	if (ac < 5 || ac > 6 || !check(av))
		return (1);
	args = malloc(sizeof(t_args));
	if (init_values(&args, av))
		return (1);
	data = malloc(sizeof(t_philo) * args->ph_num);
	args->time_start = my_time();
	data = init_my_data(data, args);
	philo = malloc(sizeof(pthread_t) * args->ph_num);
	while (i < args->ph_num)
	{
		if (pthread_create(&philo[i], NULL, routine, &data[i]))
			return (1);
		i++;
	}
	if (check_dead(args, data))
		return (1);
}
