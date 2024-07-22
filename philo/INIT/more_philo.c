/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:22:08 by sgalli            #+#    #+#             */
/*   Updated: 2023/06/20 13:52:30 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	more_forks(t_phil *p)
{
	int	i;

	i = -1;
	while (++i < p->n_phil)
		pthread_mutex_init(&p->forks[i], NULL);
	i = -1;
	while (++i < p->n_phil)
	{
		p[i].left_fork = &p->forks[i];
		if (i == p->n_phil - 1)
			p[i].right_fork = &p->forks[0];
		else
			p[i].right_fork = &p->forks[i + 1];
	}
}

void	more_phil(t_phil *p, char **v)
{
	int	i;

	i = -1;
	while (++i < p->n_phil)
	{
		p[i].n_phil = ft_atoi(v[1]);
		p[i].id = i + 1;
		p[i].a = p[0].a;
		p[i].check = 0;
		p[i].single_eating = 0;
		pthread_mutex_init(&p[i].lock, NULL);
	}
}

void	alive(t_phil *p_inf, int c, char **v)
{
	p_inf->n_phil = ft_atoi(v[1]);
	p_inf->a = malloc(sizeof(struct s_alive));
	if (p_inf->a == NULL)
	{
		free(p_inf);
		return (final_exit(&p_inf));
	}
	if (c == 6)
		p_inf->a->max_eat = ft_atoi(v[5]);
	else
		p_inf->a->max_eat = -1;
	p_inf->a->start_time = p_time();
	p_inf->a->t_sleep = ft_atoi(v[4]);
	p_inf->a->t_die = ft_atoi(v[2]);
	p_inf->a->t_eat = ft_atoi(v[3]);
	p_inf->a->exit = 0;
	p_inf->a->fin = 0;
	pthread_mutex_init(&p_inf->a->lockeat, NULL);
	pthread_mutex_init(&p_inf->a->lockfin_die, NULL);
	pthread_mutex_init(&p_inf->a->messager, NULL);
}

void	start_more(char **v, int c, t_phil *p_inf)
{
	alive(p_inf, c, v);
	p_inf->thread_id = malloc(sizeof(pthread_t *) * p_inf->n_phil);
	p_inf->forks = malloc(sizeof(pthread_mutex_t) * p_inf->n_phil);
	if (p_inf->forks == NULL || p_inf->thread_id == NULL \
	|| p_inf == NULL)
		return (final_exit(&p_inf));
	pthread_mutex_init(&p_inf->lock, NULL);
	more_forks(p_inf);
	more_phil(p_inf, v);
}
