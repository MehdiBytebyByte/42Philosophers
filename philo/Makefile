# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboughra <mboughra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:45:53 by mboughra          #+#    #+#              #
#    Updated: 2024/12/11 13:16:22 by mboughra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c src/parse.c src/tools.c src/init.c src/init2.c src/routine.c src/createnjoin.c src/garbageco.c \
		src/ft_usleep.c src/monitor.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
HEADER = include/philo.h
CC = cc

all: $(NAME)
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	# rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
clean:
	rm -f $(OBJS)
re: fclean all
.PHONY: clean all fclean re