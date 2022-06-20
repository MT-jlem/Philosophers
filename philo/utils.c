/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:20:22 by mjlem             #+#    #+#             */
/*   Updated: 2022/06/17 16:22:50 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean(t_args *args, pthread_t *philo, t_philo *data)
{
	int	i;

	i = 0;
	while (i < args->ph_num)
		pthread_mutex_destroy(&args->fork[i++]);
	pthread_mutex_destroy(&args->print);
	free(args->fork);
	free(args);
	free(data);
	free(philo);
	return (0);
}
