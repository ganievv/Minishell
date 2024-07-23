# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 01:08:28 by tnakas            #+#    #+#              #
#    Updated: 2024/07/23 13:13:46 by tnakas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I$(LIBFT_DIR)
LIBFT_DIR = libft

SRC = src/parser.c src/main.c src/signals.c \
		src/builtins_1.c src/builtins_2.c src/l_utils_one.c \
		src/l_utils_two.c src/utils_exec.c

OBJ = $(SRC:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(BLUE)Linking $@...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline
	@echo "$(GREEN)Executable $(NAME) created successfully!$(RESET)"

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@echo "$(GREEN)Library libft created successfully!$(RESET)"

%.o: %.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@rm -f $(OBJ)
	@echo "$(YELLOW)Cleaned up object files and temporary files.$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning all build files...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@rm -f $(NAME)
	@echo "$(RED)Fully cleaned including executable and libraries.$(RESET)"

re: fclean all

.PHONY: all clean fclean re