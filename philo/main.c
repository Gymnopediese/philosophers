/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:05:43 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 15:56:58 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#define ERROR "usage: number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"

t_table	*get_table(void)
{
	static t_table	t[1];

	return (t);
}

void	finish(char *message)
{
	t_table			*t;
	int				i;

	t = get_table();
	i = -1;
	while (++i < t->data.phil_amount)
	{
		if (t->philos[i].hasfork)
			pthread_mutex_destroy(&t->philos[i].fork);
		if (t->philos[i].is_running)
			pthread_detach(t->philos[i].thread);
	}
	if (message)
		printf("philosopher: %s\n", message);
	if (t->philos != 0)
		free(t->philos);
	if (t->data.m_dead != 0)
		pthread_mutex_destroy(t->data.m_dead);
	if (t->data.m_diners != 0)
		pthread_mutex_destroy(t->data.m_diners);
	if (t->data.m_print != 0)
		pthread_mutex_destroy(t->data.m_print);
	exit(0);
}

void	launch(void)
{
	int				loop;
	t_table			*t;

	t = get_table();
	loop = -1;
	while (++loop < t->data.phil_amount)
		philosopher_school(t->philos, t, loop);
	loop = -1;
	while (++loop < t->data.phil_amount)
	{
		if (pthread_create(&t->philos[loop].thread, 0,
				philosopher_life, &(t->philos[loop])) != 0)
			finish("couldn't create thread");
		t->philos[loop].is_running = 1;
	}
	loop = -1;
	while (++loop < t->data.phil_amount)
	{
		if (pthread_join(t->philos[loop].thread, 0) != 0)
			finish("couldn't join thread");
	}
}

int	main(int argc, char **argv)
{
	t_table	*t;

	t = get_table();
	memset(t, 0, sizeof(t_table));
	if (argc < 5 || argc > 6)
		error(ERROR, 0);
	if (!set_the_table(t, argc, argv))
		return (1);
	t->philos = malloc(sizeof(t_philosophe) * t->data.phil_amount);
	if (t->philos == 0)
		finish("malloc error");
	memset(t->philos, 0, sizeof(t_philosophe) * t->data.phil_amount);
	launch();
	finish(0);
}
