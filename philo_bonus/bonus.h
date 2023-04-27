/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:29:54 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 13:46:35 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <semaphore.h>
# include <stdarg.h>
# include <sys/errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <string.h>

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
	sem_t			*forks;
	sem_t			*finished;
	sem_t			*dead;
	sem_t			*print;
	int				*pids;
	int				exit;
	pthread_t		*win;
	pthread_t		*loose;
}	t_have;

// typedef struct s_table
// {
// 	int				died;
// 	int				fullphill;
// 	t_have			data;
// }	t_table;

typedef struct s_philosophe
{
	int					name;
	long long			time_before_dying;
	t_have				data;
	int					diners;
	int					hasfork;
	int					pid;
}	t_philosophe;


void			ft_sem_close(sem_t *sem, char *name);
long long int	gettimem(void);
void			error(char *message, ...);
void			message(t_philosophe	*phil, char *word);

int				ft_atoi(const char *str);
long long int	gettime(void);
void			lonly_life(t_have *t);
void			finish(char *message, t_have *t);
void			*w(void *w);
sem_t			*ft_sem_open(char *name, int val, t_have *table);
int				*mode(void);
int				f(void *ptr);
int				ft_usleep(int time);
int				set_the_table(t_have *table, int argc, char **argv);
void			philosopher_school(t_philosophe *phil, int name);
void			*philosopher_life(void *ptr);
void			ft_msleep(int time);
#endif