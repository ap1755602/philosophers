# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frodney <frodney@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/18 18:32:00 by frodney           #+#    #+#              #
#    Updated: 2021/08/22 01:01:24 by frodney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
FLAGS = -Wall -Werror -Wextra -O3 -g
INCLUDES = -I$(HEADER_DIR)

HEADER_DIR = ./includes/
HEADER =  $(addprefix $(HEADER_DIR), philosophers.h)

SRC_DIR = ./sources/
SRC_LIST = main.c phill.c init_th_and_mut.c free.c ward.c \
	create_filos.c time_funcs.c atoi.c lst_funcs.c

SRC = $(SRC_DIR)/$(SRC_LIST)

OBJ_DIR = ./objects/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re 

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(HEADER)
	@$(CC) $(INCLUDES) $(OBJ) -o $(NAME) #$(FLAGS)
	@echo "\n$(NAME): $(GREEN)object files and directory ./objects/ were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)object files and directory ./objects/ were deleted$(RESET)"

norm:
	@norminette $(SRC_DIR)*.c $(HEADER_DIR)*.h

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
