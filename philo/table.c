/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:29:19 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 15:48:36 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_errors(t_table *table)
{
	if (table->data.time_to_die <= 0
		|| table->data.time_to_eat <= 0 || table->data.time_to_slp <= 0)
		finish("arrguments cannot be negatives or 0");
	if (table->data.phil_amount < 0)
		finish("cannot have less than 0 philospher,\
 it does not make any sens, or does it?");
	if (table->data.phil_amount == 0)
		finish("phewww, it's calm in here");
	return (0);
}

int	set_the_table(t_table *table, int argc, char **argv)
{
	table->data.phil_amount = ft_atoi(argv[1]);
	table->data.time_to_die = ft_atoi(argv[2]);
	table->data.time_to_eat = ft_atoi(argv[3]);
	table->data.time_to_slp = ft_atoi(argv[4]);
	table->data.diners = -1;
	if (argc == 6)
		table->data.diners = ft_atoi(argv[5]);
	check_errors(table);
	if (pthread_mutex_init(&table->m_print, 0))
		finish("mutex cannot allocate");
	table->data.m_print = &table->m_print;
	if (pthread_mutex_init(&table->m_dead, 0))
		finish("mutex cannot allocate");
	table->data.m_dead = &table->m_dead;
	if (pthread_mutex_init(&table->m_diners, 0))
		finish("mutex cannot allocate");
	table->data.m_diners = &table->m_diners;
	table->fullphill = 0;
	table->data.fullphill = &table->fullphill;
	table->died = -1;
	table->data.died = &table->died;
	table->data.timer = gettimem();
	return (1);
}
