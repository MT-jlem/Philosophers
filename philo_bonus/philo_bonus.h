/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 08:47:19 by mjlem             #+#    #+#             */
/*   Updated: 2022/06/10 09:27:21 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef long long	t_time;

int		check(char **av);
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);
t_time	my_time(void);
void	my_sleep(t_time time);

#endif