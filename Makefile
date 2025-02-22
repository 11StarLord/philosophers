# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djoao <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 09:07:48 by djoao             #+#    #+#              #
#    Updated: 2025/02/10 09:07:51 by djoao            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	main.c		\
	utils.c		\
	validation.c	\
	start_structs.c		\
	philo_routines.c

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@sleep 1
	clear

all:	$(NAME)

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)
	@sleep 1
	clear

re:	fclean all

.PHONY:	all clean fclean re
