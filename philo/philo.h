/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:52:25 by mjlem             #+#    #+#             */
/*   Updated: 2022/06/07 15:19:20 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef long long	t_time;

typedef struct s_args
{
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	t_time			time_start;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}	t_args;

typedef struct s_philo
{
	int		id;
	t_time	last_meal;
	t_args	*args;
	int		meal_count;
	int		is_eating;
}	t_philo;

int		check(char **av);
int		ft_atoi(char *str);
int		init_values(t_args **args, char **av);
int		ft_strcmp(char *s1, char *s2);
t_time	my_time(void);
t_philo	*init_my_data(t_philo *data, t_args *args);
void	my_sleep(t_time time);

#endif