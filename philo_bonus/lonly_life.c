/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonly_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:26:24 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 11:11:04 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	f(void *ptr)
{
	free(ptr);
	return (1);
}

void	lonly_life(t_have *t)
{
	char	**mess;
	int		i;

	mess = (char *[]){
		"1 is thinking alone, wondering how will he eat with only one fork.\n",
		"1 think that this situation doesn't make any sens...\n",
		"1 is supposed to use his hands to eat or something like that?\n",
		"1, even with his 3 masters in philosophie, phisiques and\
 mathematiques, can't come up with any ideas on how to eat...\n",
		"1 is now naked on the table, he gave up and prefer\
 spending the rest of his life dancing, something he never did before.\n",
		"1 died, who would have guessed?\n"
	};
	i = -1;
	while (++i < 6)
	{
		printf("%i\t%s", t->time_to_die * i / 5, mess[i]);
		ft_usleep(t->time_to_die / 5);
	}
	exit(0);
}
