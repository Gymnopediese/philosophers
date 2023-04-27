/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:29:54 by albaud            #+#    #+#             */
/*   Updated: 2023/04/26 12:48:41 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdarg.h>
# include <sys/errno.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# include <semaphore.h>

// int				*fullphill;
// int				*died;
// pthread_mutex_t	*mutex;
// pthread_mutex_t	*m_diners;
// pthread_mutex_t	*m_dead;
typedef struct s_have
{
	long long		timer;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_slp;
	int				diners;
	int				phil_amount;
	int				*fullphill;
	int				*died;
	pthread_mutex_t	*m_print;
	pthread_mutex_t	*m_diners;
	pthread_mutex_t	*m_dead;

}	t_have;

typedef struct s_philosophe
{
	int					name;
	pthread_t			thread;
	long long			time_before_dying;
	t_have				data;
	int					diners;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		fork;
	int					hasfork;
	int					is_running;
}	t_philosophe;

typedef struct s_table
{
	int				died;
	int				fullphill;
	t_have			data;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_diners;
	pthread_mutex_t	m_dead;
	t_philosophe	*philos;
}	t_table;

void			finish(char *message);
long long int	gettimem(void);
void			error(char *message, ...);
void			message(t_philosophe	*phil, char *word);
int				set_the_table(t_table *table, int argc, char **argv);

void			philosopher_school(t_philosophe *phil,
					t_table *table, int name);
int				ft_atoi(const char *str);
long long int	gettime(void);
int				check_errors(t_table *table);

void			*w(void *w);
sem_t			*ft_sem_open(char *name, int val);
int				*mode(void);
int				f(void *ptr);
int				ft_usleep(int time);

void			*philosopher_life(void *ptr);
void			ft_msleep(int time);
void			lonly_life(t_table *t);
#endif