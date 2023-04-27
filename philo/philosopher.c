/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:39:29 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 15:53:45 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*is_dead(void *philo)
{
	t_philosophe	*phil;

	phil = philo;
	if (gettimem() - phil->time_before_dying > phil->data.time_to_die * 1000)
	{
		pthread_mutex_lock(phil->data.m_print);
		printf("%lli %i %s\n",
			(gettimem() - phil->data.timer) / 1000, phil->name, "is dead");
		finish(0);
	}
	pthread_mutex_lock(phil->data.m_diners);
	if (*phil->data.fullphill == phil->data.phil_amount)
	{
		pthread_mutex_lock(phil->data.m_print);
		printf("%lli %i %s\n",
			(gettimem() - phil->data.timer) / 1000, phil->name,
			"noticed that all philosopher were full");
		finish(0);
	}
	pthread_mutex_unlock(phil->data.m_diners);
	return (0);
}

void	sleeps(t_philosophe	*phil)
{
	message(phil, "is sleeping");
	pthread_mutex_unlock(phil->rfork);
	pthread_mutex_unlock(&phil->fork);
	ft_usleep(phil->data.time_to_slp);
	is_dead(phil);
	message(phil, "is thinking");
}

int	eat(t_philosophe	*phil)
{
	phil->time_before_dying = gettimem();
	message(phil, "has taken a fork");
	message(phil, "has taken a fork");
	message(phil, "is eating");
	if (++phil->diners == phil->data.diners)
	{
		pthread_mutex_lock(phil->data.m_diners);
		*phil->data.fullphill += 1;
		pthread_mutex_unlock(phil->data.m_diners);
	}
	ft_usleep(phil->data.time_to_eat);
	sleeps(phil);
	return (1);
}

void	*philosopher_life(void *ptr)
{
	t_philosophe	*phil;
	pthread_t		t;

	(void)t;
	phil = (t_philosophe *) ptr;
	message(phil, "is thinking");
	if (phil->data.phil_amount == 1)
		ft_usleep(phil->data.time_to_die);
	else if (phil->name % 2 == 0)
		ft_usleep(phil->data.time_to_eat / 10);
	while (1)
	{
		is_dead(phil);
		pthread_mutex_lock(&phil->fork);
		pthread_mutex_lock(phil->rfork);
		is_dead(phil);
		eat(phil);
	}
	return (0);
}

void	philosopher_school(t_philosophe *phil, t_table *table, int name)
{
	phil[name].data = table->data;
	phil[name].name = name + 1;
	phil[name].hasfork = 1;
	if (name + 1 < table->data.phil_amount)
		phil[name].rfork = &phil[name + 1].fork;
	else
		phil[name].rfork = &phil[0].fork;
	phil[name].time_before_dying = gettimem();
	phil[name].diners = 0;
	pthread_mutex_init(&phil[name].fork, 0);
	phil[name].hasfork = 1;
}
