/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:26 by sgalli            #+#    #+#             */
/*   Updated: 2023/06/20 14:14:39 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	p_status(char *s, t_phil *p)
{
	pthread_mutex_lock(&p->a->messager);
	if (p->a->exit == 0)
	{
		pthread_mutex_unlock(&p->a->messager);
		pthread_mutex_lock(&p->a->messager);
		printf("%lld %d %s\n", p_time() - p->a->start_time, p->id, s);
		pthread_mutex_unlock(&p->a->messager);
		return ;
	}
	pthread_mutex_unlock(&p->a->messager);
}

void	take_fork_drop(t_phil *p)
{
	if (p->id == p->n_phil)
	{
		pthread_mutex_lock(p->left_fork);
		p_status("has taken a fork", p);
		pthread_mutex_lock(p->right_fork);
		p_status("has taken a fork", p);
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		p_status("has taken a fork", p);
		pthread_mutex_lock(p->left_fork);
		p_status("has taken a fork", p);
	}
}

void	dropping(t_phil *p)
{
	if (p->id == p->n_phil)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
	else
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
	}
}

void	waiting(long long wait)
{
	long long	t;

	t = p_time() + wait;
	while (p_time() - t < 0)
		usleep(100);
}

void	eating(t_phil *p)
{
	take_fork_drop(p);
	pthread_mutex_lock(&p->lock);
	pthread_mutex_lock(&p->a->messager);
	p->start_time_eat = p_time();
	pthread_mutex_unlock(&p->a->messager);
	p->single_eating++;
	pthread_mutex_unlock(&p->lock);
	p_status("is eating", p);
	waiting(p->a->t_eat);
	dropping(p);
}
