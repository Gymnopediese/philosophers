/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:05:08 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 11:20:25 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

long long int	gettimem(void)
{
	static struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

int	ft_usleep(int ms)
{
	long int	time;
	int			w;

	time = gettimem();
	w = ms / 20;
	ms *= 1000;
	while (gettimem() - time < ms)
		usleep(w);
	return (1);
}

long long int	gettime(void)
{
	static struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
