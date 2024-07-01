/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:25:57 by sgalli            #+#    #+#             */
/*   Updated: 2023/06/20 13:52:44 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_phil
{
	pthread_t		*thread_id;
	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*forks;
	int				n_phil;
	int				id;
	int				single_eating;
	int				check;
	long long		start_time_eat;
	struct s_alive	*a;
}					t_phil;

typedef struct s_alive
{
	pthread_mutex_t	lockeat;
	pthread_mutex_t	lockfin_die;
	pthread_mutex_t	messager;
	long long		start_time;
	long long		t_sleep;
	long long		t_eat;
	int				exit;
	int				fin;
	int				t_die;
	int				total;
	int				max_eat;
}					t_alive;

void				waiting(long long wait);
void				timer(t_phil *p);
void				p_status(char *s, t_phil *p);
void				eating(t_phil *p);
void				helper(t_phil **p_inf);
void				final_exit(t_phil **p_inf);
void				phil(t_phil *p);
void				start(char **v, int c, t_phil *p_inf);
void				more_philos(t_phil *p);
void				start_more(char **v, int c, t_phil *p_inf);
void				more_fork(t_phil *p);
void				*routine(void *p_phil);
void				*life_routine(void *p_phil);
void				*timer_death(t_phil *p);

int					invalid_arg(int c, char **v);
int					ft_atoi(const char *str);
int					ft_strcmp(char *s1, char *s2);

long long			p_time(void);

#endif
