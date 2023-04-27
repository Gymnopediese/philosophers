/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:05:43 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 13:47:27 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#define ERROR "usage: number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"

#define MAXTHREADS 1000

void	finish(char *message, t_have *t)
{
	int			i;

	i = -1;
	while (t->pids && t->pids[++i] != -1)
		kill(t->pids[i], SIGQUIT);
	if (message)
		printf("philosopher: %s\n", message);
	ft_sem_close(t->forks, "forks");
	ft_sem_close(t->print, "print");
	ft_sem_close(t->dead, "dead");
	ft_sem_close(t->finished, "finished");
	if (t->win != 0)
		pthread_detach(*t->win);
	if (t->loose != 0)
		pthread_detach(*t->loose);
	exit(t->exit);
}

void	forking(int count, t_have *to_have, int *pids)
{
	int				pid;
	t_philosophe	phil;

	if (count <= 0)
		return ;
	pid = fork();
	if (pid == -1)
		finish("couldn't fork", to_have);
	if (pid == 0)
	{
		phil.data = *to_have;
		philosopher_school(&phil, count);
		exit(0);
	}
	else
	{
		pids[to_have->phil_amount - count] = pid;
		pids[to_have->phil_amount - count + 1] = -1;
		forking(count - 1, to_have, pids);
	}
}

void	*is_dead(void *p)
{
	t_have	*table;

	table = p;
	sem_wait(table->dead);
	table->exit = 0;
	finish(0, table);
	return (0);
}

void	*are_full(void *p)
{
	t_have	*table;
	int		i;

	table = p;
	i = -1;
	while (++i < table->phil_amount)
		sem_wait(table->finished);
	sem_wait(table->print);
	table->exit = 0;
	finish("all philo are full", table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_have			table;
	pthread_t		subprocess[2];
	int				pids[MAXTHREADS];


	memset(&table, 0, sizeof(t_have));
	table.exit = 1;
	if (argc < 5 || argc > 6)
		finish(ERROR, 0);
	if (!set_the_table(&table, argc, argv))
		finish("an error accured", &table);
	table.pids = pids;
	table.pids[0] = -1;
	forking(table.phil_amount, &table, table.pids);
	if (pthread_create(&subprocess[0], 0, are_full, &table) != 0)
		finish("couldn't create thread", &table);
	table.win = &subprocess[0];
	if (pthread_create(&subprocess[1], 0, is_dead, &table) != 0)
		finish("couldn't create thread", &table);
	table.loose = &subprocess[0];
	pthread_join(subprocess[0], 0);
	pthread_join(subprocess[1], 0);
}
