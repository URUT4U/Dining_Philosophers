# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nranna <nranna@student.42.rio>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 03:26:02 by nranna            #+#    #+#              #
#    Updated: 2024/12/16 23:33:52 by nranna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CCFLAGS = -Wall -Wextra -Werror -pthread -O3
NAME = philo
GREEN = \033[1;32m
WHITE = \033[1;37m

# PROGRAM FILES CHANGE SRC LATER
SRC = data_init.c dinner_init.c main.c mutex.c mutex_utils.c parser.c sync.c \
	  threads.c utils.c waiter.c clean.c

INCLUDE = philo.h

OBJ = $(SRC:.c=.o)

all: $(NAME)
%.o: %.c $(INCLUDE)
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@echo "$(WHITE)\nCREATING [$(NAME)]..."
	@$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)[$(NAME)] OK :)$(WHITE)\n"
clean:
	@echo "$(WHITE)\nCLEANING OBJECT FILES..."
	@rm -f $(OBJ)
	@echo "$(GREEN)OK. :)$(WHITE)\n"

fclean: clean
	@echo "$(WHITE)\nCLEANING [$(NAME)]..."
	@rm -f $(NAME)
	@echo "$(GREEN)OK. :)$(WHITE)\n"

re: fclean all

.PHONY: all clean fclean re
