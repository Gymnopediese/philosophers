/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:39:29 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 15:55:09 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	die(t_philosophe *phil, long long int start)
{
	if (gettime() - start < phil->data.time_to_die)
		return ;
	sem_post(phil->data.dead);
	sem_wait(phil->data.print);
	printf("%lli %i %s\t\n",
		(gettimem() - phil->data.timer) / 1000, phil->name, "is dead");
	exit(0);
}

void	life_cycle(t_philosophe *phil, long long int *start)
{
	sem_wait(phil->data.forks);
	die(phil, *start);
	*start = gettime();
	message(phil, "has taken a fork");
	message(phil, "has taken a fork");
	message(phil, "is eating");
	ft_usleep(phil->data.time_to_eat);
	die(phil, *start);
	if (phil->diners++ == phil->data.diners)
		sem_post(phil->data.finished);
	sem_post(phil->data.forks);
	message(phil, "is sleeping");
	ft_usleep(phil->data.time_to_slp);
	die(phil, *start);
	message(phil, "is thinking");
}

void	*philosopher_life(void *ptr)
{
	t_philosophe	*phil;	
	long long int	start;

	phil = (t_philosophe *) ptr;
	start = gettime();
	message(phil, "is thinking");
	if (phil->data.phil_amount == 1)
		ft_usleep(phil->data.time_to_die);
	else if (phil->name % 2)
		ft_usleep(phil->data.time_to_eat / 10);
	die(phil, start);
	while (1)
	{
		life_cycle(phil, &start);
	}
	return (0);
}

void	philosopher_school(t_philosophe *phil, int name)
{
	phil->name = name;
	phil->diners = 0;
	philosopher_life(phil);
}
