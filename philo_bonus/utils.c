/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <mjlem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:27:07 by mjlem             #+#    #+#             */
/*   Updated: 2022/06/19 17:52:53 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	clean(t_args *args, t_data *data, int *p_id)
{
	free(args);
	free(p_id);
	free(data);
	return (0);
}

void	clean_exit(int	*id, t_args *args)
{
	int	i;
	int	p_id;
	int	stat;

	p_id = waitpid(-1, &stat, 0);
	i = 0;
	if (stat == 0)
	{	
		while (i < args->ph_num)
		{
			if (id[i] == p_id)
				i++;
			kill(id[i], 2);
			i++;
		}
	}
	else
		while (++i < args->ph_num)
			waitpid(-1, NULL, 0);
	sem_close(args->fork);
	sem_close(args->print);
	sem_unlink("/forks");
	sem_unlink("/print");
	exit(0);
}
