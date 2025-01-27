NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCS =	./srcs/philosopher.c		\
		./srcs/utils.c				\
		./srcs/validation.c			\

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
