/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:33:09 by sgalli            #+#    #+#             */
/*   Updated: 2023/06/16 10:57:16 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	phil(t_phil *p)
{
	p->forks = malloc(sizeof(pthread_mutex_t));
	p->thread_id = malloc(sizeof(pthread_t *));
	if (p->forks == 0 || p->thread_id == 0)
		return (final_exit(&p));
	pthread_mutex_init(&p->forks[0], NULL);
	p[0].left_fork = &p->forks[0];
	p[0].id = 1;
}

void	start_alive(t_phil *p, char **v, int c)
{
	p->a = malloc(sizeof(struct s_alive));
	p->a->start_time = p_time();
	p->a->t_die = ft_atoi(v[2]);
	p->a->t_eat = ft_atoi(v[3]);
	p->a->exit = 0;
	p->a->t_sleep = ft_atoi(v[4]);
	if (c == 6)
		p->a->max_eat = ft_atoi(v[5]);
	else
		p->a->max_eat = -1;
}

void	start(char **v, int c, t_phil *p_inf)
{
	start_alive(p_inf, v, c);
	p_inf->n_phil = 1;
	pthread_mutex_init(&p_inf->lock, NULL);
	return (phil(p_inf));
}
