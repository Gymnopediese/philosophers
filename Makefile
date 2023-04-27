# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 18:46:11 by albaud            #+#    #+#              #
#    Updated: 2023/04/27 16:26:53 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 	= philo/main.c philo/table.c philo/philosopher.c philo/outputs.c philo/ft_atoi.c philo/lonly_life.c philo/time.c
BUNOS 	= philo_bonus/ft_atoi.c philo_bonus/lonly_life.c philo_bonus/main.c philo_bonus/outputs.c philo_bonus/philosopher.c philo_bonus/sems.c philo_bonus/table.c philo_bonus/time.c
OBJS 	= ${SRCS:.c=.o}
BOBJS 	= ${BUNOS:.c=.o}
NAME 	= philosophers
BNAME 	= bonus_philosophers
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

.c.o 	:
		${CC} ${CFLAGS} -I /usr/X11/include -c $< -o ${<:.c=.o}
		
all 	: $(NAME)

bonus	:$(BNAME)
		
$(BNAME): ${BOBJS} 
		${CC} ${CFLAGS} -o $(BNAME) $(BOBJS)

$(NAME)	: ${OBJS}
		${CC} ${CFLAGS} -o $(NAME) $(OBJS)

clean	:
		rm -f ${OBJS} ${LIB}

fclean	:	clean
		rm -f ${NAME}

bclean	:
		rm -f ${BOBJS} ${LIB}

bfclean	:	bclean
		rm -f ${BNAME}

bre: bfclean
		make bonus

re		: fclean all
san: 
	gcc -fsanitize=thread $(SRCS) -o sane
	./sane 10 410 200 200 10