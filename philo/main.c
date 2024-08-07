/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:15:24 by sgalli            #+#    #+#             */
/*   Updated: 2023/05/15 14:47:1 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/philo.h"

void	one_phil(t_phil *p)
{
	if (pthread_create(&p->thread_id[0], NULL, routine, &p[0]) != 0)
		return (final_exit(&p));
	pthread_join(p->thread_id[0], NULL);
}

int	invalid_arg(int c, char **v)
{
	int	i;
	int	j;

	j = 1;
	if (c != 5 && c != 6)
		return (0);
	while (v[j] != NULL)
	{
		i = 0;
		while (v[j][i] != '\0')
		{
			if (v[j][i] < '0' || v[j][i] > '9')
				return (0);
			i++;
		}
		j++;
	}
	if (ft_atoi(v[1]) <= 0 || ft_atoi(v[1]) > 200 || ft_atoi(v[2]) <= 0
		|| ft_atoi(v[3]) <= 0 || ft_atoi(v[4]) <= 0)
		return (0);
	if (c == 6)
		if (ft_atoi(v[5]) <= 0)
			return (0);
	return (1);
}

int	main(int c, char **v)
{
	t_phil	*p;

	if (invalid_arg(c, v) == 0)
	{
		printf("Error\n");
		return (0);
	}
	p = (t_phil *)malloc(sizeof(t_phil) * ft_atoi(v[1]));
	if (ft_atoi(v[1]) == 1)
	{
		start(v, c, p);
		one_phil(p);
	}
	else
	{
		start_more(v, c, p);
		more_philos(p);
	}
	free((p->a));
	final_exit(&p);
	if (p != NULL)
		free(p);
}
