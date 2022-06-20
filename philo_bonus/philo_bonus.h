/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:47:19 by mjlem             #+#    #+#             */
/*   Updated: 2022/06/17 17:29:34 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

typedef long long	t_time;

typedef struct s_args
{
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	t_time			time_start;
	sem_t			*fork;
	sem_t			*print;
}	t_args;

typedef struct s_data
{
	int		ph_id;
	t_time	last_meal;
	t_args	*args;
	int		is_eating;
}	t_data;

int		check(char **av);
int		init_values(t_args **args, char **av);
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);
t_time	my_time(void);
void	my_sleep(t_time time);
int		clean(t_args *args, t_data *data, int *p_id);
void	clean_exit(int	*id, t_args *args);

#endif