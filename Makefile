NAME	= philo
CC		= cc
FLAGS	= -Wall -Wextra -Werror -g -pthread
RM		= rm -f
HEADER	= mandatory/philo.h
SRC		= mandatory/philo.c mandatory/parcing.c \
		mandatory/philo_utils.c mandatory/init_table.c \
		mandatory/philos_procces.c
OBJS	= $(SRC:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -fsanitize=address

%.o		: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

test	:
	make && make clean && clear && ./philo 5 100 100 100

.PHONY	: clean