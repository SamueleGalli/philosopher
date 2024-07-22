/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:17:49 by sgalli            #+#    #+#             */
/*   Updated: 2023/06/16 11:24:41 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long long	p_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	helper(t_phil **p_inf)
{
	if ((*p_inf)->forks != NULL)
	{
		free((*p_inf)->forks);
		(*p_inf)->forks = NULL;
	}
	if ((*p_inf)->thread_id != NULL)
	{
		free((*p_inf)->thread_id);
		(*p_inf)->thread_id = NULL;
	}
}

void	final_exit(t_phil **p_inf)
{
	int	i;

	if (*p_inf == NULL || (*p_inf)->forks == 0)
		return ;
	if ((*p_inf)->n_phil != 0)
	{
		i = -1;
		while (++i < (*p_inf)->n_phil)
		{
			pthread_mutex_destroy(&(*p_inf)->forks[i]);
			pthread_mutex_destroy(&(*p_inf)[i].lock);
		}
		if ((*p_inf)->n_phil >= 2)
		{
			pthread_mutex_destroy(&(*p_inf)->a->lockfin_die);
			pthread_mutex_destroy(&(*p_inf)->a->lockeat);
			pthread_mutex_destroy(&(*p_inf)->a->messager);
		}
	}
	helper(p_inf);
}
