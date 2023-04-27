/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:31:30 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 15:49:21 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#define NAME "philosopher: "

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i += 1;
	}
}

void	error(char *message, ...)
{
	va_list	t;
	char	*next;

	va_start(t, message);
	ft_putstr(NAME);
	ft_putstr(message);
	next = va_arg(t, char *);
	while (next)
	{
		ft_putstr(next);
		next = va_arg(t, char *);
	}
	ft_putstr("\n");
	exit(1);
}

void	message(t_philosophe	*phil, char *word)
{
	pthread_mutex_lock(phil->data.m_print);
	printf("%lli %i %s\t\n",
		(gettimem() - phil->data.timer) / 1000, phil->name, word);
	pthread_mutex_unlock(phil->data.m_print);
}

// void	error(char *message, ...)
// {
// 	va_list	t;
// 	char	*next;

// 	va_start(t, message);
// 	ft_putstr(NAME);
// 	ft_putstr(message);
// 	next = va_arg(t, char *);
// 	while (next)
// 	{
// 		ft_putstr(next);
// 		next = va_arg(t, char *);
// 	}
// 	ft_putstr("\n");
// 	exit(1);
// }