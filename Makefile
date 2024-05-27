NAME	= philo
CC		= cc
FLAGS	= -Wall -Wextra -Werror -g -pthread
RM		= rm -f
HEADER	= mandatory/philo.h
SRC		= mandatory/philo.c
OBJS	= $(SRC:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o		: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

.PHONY	: clean