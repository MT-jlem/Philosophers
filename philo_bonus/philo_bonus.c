/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:45:30 by mjlem             #+#    #+#             */
/*   Updated: 2022/06/17 17:29:41 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *args)
{
	t_data	*data;

	data = (t_data *) args;
	usleep(500);
	while (1)
	{
		if (my_time() - data->last_meal > data->args->t_die && data->is_eating)
		{
			sem_wait(data->args->print);
			printf("%lld %d died\n",
				(my_time() - data->args->time_start), data->ph_id);
			exit(0);
		}
		if (data->args->num_eat == 0)
			exit(1);
	}
	return (data);
}

void	is_eating(t_data **data)
{
	sem_wait((*data)->args->fork);
	sem_wait((*data)->args->print);
	printf("%lld %d has taken a fork\n",
		(my_time() - (*data)->args->time_start), (*data)->ph_id);
	sem_post((*data)->args->print);
	sem_wait((*data)->args->fork);
	sem_wait((*data)->args->print);
	printf("%lld %d has taken a fork\n",
		(my_time() - (*data)->args->time_start), (*data)->ph_id);
	sem_post((*data)->args->print);
	sem_wait((*data)->args->print);
	printf("%lld %d is eating\n",
		(my_time() - (*data)->args->time_start), (*data)->ph_id);
	sem_post((*data)->args->print);
	(*data)->last_meal = my_time();
	(*data)->is_eating = 0;
	my_sleep((*data)->args->t_eat);
	(*data)->is_eating = 1;
	sem_post((*data)->args->fork);
	sem_post((*data)->args->fork);
	if ((*data)->args->num_eat > 0)
		(*data)->args->num_eat--;
}

void	routine(t_data **data)
{
	if ((*data)->ph_id % 2)
		usleep(500);
	while ((*data)->args->num_eat != 0)
	{
		is_eating(data);
		sem_wait((*data)->args->print);
		printf("%lld %d is sleeping\n",
			(my_time() - (*data)->args->time_start), (*data)->ph_id);
		sem_post((*data)->args->print);
		my_sleep((*data)->args->t_sleep);
		sem_wait((*data)->args->print);
		printf("%lld %d is thinking\n",
			(my_time() - (*data)->args->time_start), (*data)->ph_id);
		sem_post((*data)->args->print);
	}
}

int	*start_rou(t_args *args, t_data *data, int *p_id)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < args->ph_num)
	{
		p_id[i] = fork();
		if (p_id[i] == 0)
		{
			data->args = args;
			data->last_meal = my_time();
			data->is_eating = 1;
			pthread_create(&thread, NULL, check_death, data);
			pthread_detach(thread);
			routine(&data);
		}
		i++;
		data->ph_id++;
	}
	return (p_id);
}

int	main(int ac, char **av)
{
	t_args		*args;
	t_data		*data;
	int			*p_id;

	if (ac < 5 || ac > 6 || !check(av))
		return (1);
	args = malloc (sizeof(t_args));
	init_values(&args, av);
	p_id = malloc(sizeof(int) * args->ph_num);
	data = malloc (sizeof(t_data));
	data->ph_id = 1;
	sem_unlink("/forks");
	sem_unlink("/print");
	args->fork = sem_open("/forks", O_CREAT, S_IRUSR | S_IWUSR, args->ph_num);
	args->print = sem_open("/print", O_CREAT, S_IRUSR | S_IWUSR, 1);
	p_id = start_rou(args, data, p_id);
	clean_exit(p_id, args);
	return (clean(args, data, p_id));
}
