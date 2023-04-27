/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sems.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 08:11:56 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 13:46:14 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

sem_t	*ft_sem_open(char *name, int val, t_have *table)
{
	sem_t	*sem;

	errno = 0;
	sem = sem_open(name, O_CREAT, 0666, val);
	if (sem == SEM_FAILED)
		finish("semaphore is not working bro", table);
	return (sem);
}

void	ft_sem_close(sem_t *sem, char *name)
{
	if (sem == 0)
		return ;
	sem_post(sem);
	sem_unlink(name);
	sem_close(sem);
}
