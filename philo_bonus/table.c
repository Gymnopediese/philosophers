/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:29:19 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 15:56:46 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	check_errors(t_have *table)
{
	if (table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_slp <= 0)
		error("arrguments cannot be negatives or 0", 0);
	if (table->phil_amount < 0)
		error("cannot have less than 0 philospher,\
 it does not make any sens, or does it?", 0);
	if (table->phil_amount == 0)
		error("phewww, it's calm in here", 0);
	return (0);
}

int	set_the_table(t_have *table, int argc, char **argv)
{
	if (argc < 5)
		return (0);
	table->phil_amount = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_slp = ft_atoi(argv[4]);
	table->diners = -1;
	if (argc == 6)
		table->diners = ft_atoi(argv[5]);
	check_errors(table);
	sem_unlink("forks");
	table->forks = ft_sem_open("forks", table->phil_amount / 2, table);
	sem_unlink("dead");
	table->dead = ft_sem_open("dead", 0, table);
	sem_unlink("finished");
	table->finished = ft_sem_open("finished", 0, table);
	sem_unlink("print");
	table->print = ft_sem_open("print", 1, table);
	table->timer = gettimem();
	return (1);
}
