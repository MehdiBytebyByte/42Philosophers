
NAME = Philosophers
SRCS = main.c parse.c tools.c init.c routine.c

OBJS = $(SRCS:.c=.o)
# FLAGS = -Wall -Wextra -Werror
HEADER = philo.h

do: all clean
all: $(NAME)
%.o: %.c $(HEADER)
	$(CC) -g -fsanitize=address $(FLAGS) -c $< -o $@ 
$(NAME): $(OBJS)
	$(CC) -g -fsanitize=address $(FLAGS) $(OBJS) -o $(NAME)
	# rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
clean:
	rm -f $(OBJS)
re: fclean all
.PHONY: clean