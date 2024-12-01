NAME = Philosophers
SRCS = src/main.c src/parse.c src/tools.c src/init.c src/routine.c src/createnjoin.c src/garbageco.c

OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror -g -pthread
# FLAGS = -Wall -Wextra -Werror  -g -fsanitize=address
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