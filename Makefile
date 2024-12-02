NAME = philo
SRCS = main.c src/parse.c src/tools.c src/init.c src/init2.c src/routine.c src/createnjoin.c src/garbageco.c \
		src/ft_usleep.c src/one_philo.c

OBJS = $(SRCS:.c=.o)
# FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
# FLAGS = -Wall -Wextra -Werror
FLAGS = -Wall -Wextra -Werror  -g -fsanitize=thread
HEADER = include/philo.h
CC = gcc

# do: all clean
all: $(NAME)
%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ 
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	# rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
clean:
	rm -f $(OBJS)
re: fclean all
.PHONY: clean all fclean re