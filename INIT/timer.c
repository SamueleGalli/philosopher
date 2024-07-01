/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:31:08 by sgalli            #+#    #+#             */
/*   Updated: 2023/06/20 14:17:54 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	checkin(t_phil *p, long long t, int i)
{
	pthread_mutex_lock(&p->lock);
	pthread_mutex_lock(&p->a->messager);
	if (p->check == 0)
	{
		if ((t - p[i].start_time_eat) > p->a->t_die)
		{
			pthread_mutex_unlock(&p->a->messager);
			pthread_mutex_unlock(&p->lock);
			p_status("is died", p);
			pthread_mutex_lock(&p->a->messager);
			p->a->exit = 1;
			pthread_mutex_unlock(&p->a->messager);
			return (1);
		}
	}
	pthread_mutex_unlock(&p->a->messager);
	pthread_mutex_unlock(&p->lock);
	return (0);
}

void	continuing_death(t_phil *p)
{
	int			i;
	long long	t;

	i = 0;
	while (i < p->n_phil)
	{
		t = p_time();
		if (checkin(p, t, i) == 1)
			break ;
		i++;
	}
}

void	*timer_death(t_phil *p)
{
	while (1)
	{
		pthread_mutex_lock(&p->a->messager);
		if (p->a->exit == 1)
		{
			pthread_mutex_unlock(&p->a->messager);
			break ;
		}
		if (p->a->fin == p->n_phil)
		{
			p->a->exit = 1;
			pthread_mutex_unlock(&p->a->messager);
			break ;
		}
		pthread_mutex_unlock(&p->a->messager);
		continuing_death(p);
	}
	return (0);
}
