/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:48:43 by sgalli            #+#    #+#             */
/*   Updated: 2023/06/20 14:32:25 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philo.h"

void	routining(t_phil *p)
{
	p_status("is sleeping", p);
	waiting(p->a->t_sleep);
	p_status("is thinking", p);
}

int	all_eat(t_phil *p)
{
	if (p->single_eating == p->a->max_eat)
	{
		pthread_mutex_lock(&p->a->messager);
		p->a->fin = p->a->fin + 1;
		pthread_mutex_unlock(&p->a->messager);
		pthread_mutex_lock(&p->lock);
		p->check = 1;
		pthread_mutex_unlock(&p->lock);
		pthread_mutex_lock(&p->a->messager);
		if (p->a->fin == p->n_phil)
		{
			p->a->exit = 1;
			pthread_mutex_unlock(&p->a->messager);
			return (1);
		}
		pthread_mutex_unlock(&p->a->messager);
		return (1);
	}
	return (0);
}

void	*life_routine(void *p_phil)
{
	t_phil	*p;

	p = p_phil;
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&p->a->messager);
		if (p->a->exit == 1)
		{
			pthread_mutex_unlock(&p->a->messager);
			break ;
		}
		pthread_mutex_unlock(&p->a->messager);
		if (all_eat(p) == 1)
			break ;
		eating(p);
		if (all_eat(p) == 1)
			break ;
		routining(p);
	}
	return (0);
}

void	*routine(void *p_phil)
{
	t_phil	*p;

	p = (t_phil *)p_phil;
	printf("%lld %d %s\n", p_time() - p->a->start_time, p->id, "is eating");
	while (1)
	{
		if (p_time() - p->a->start_time > p->a->t_die)
		{
			printf("%lld %d %s\n", p_time() - p->a->start_time, p->id, \
					"is died");
			return (0);
		}
	}
	return (0);
}

void	more_philos(t_phil *p)
{
	int	i;

	i = -1;
	while (++i < p->n_phil)
	{
		p[i].start_time_eat = p_time();
		pthread_create(&p->thread_id[i], NULL, life_routine, (void *)&p[i]);
	}
	timer_death(p);
	i = -1;
	while (++i < p->n_phil)
		pthread_join(p->thread_id[i], NULL);
	final_exit(&p);
}
