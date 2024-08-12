# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 01:08:28 by tnakas            #+#    #+#              #
#    Updated: 2024/08/12 16:16:47 by sganiev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I$(LIBFT_DIR)
LIBFT_DIR = libft

SRC = src/main/main.c src/main/u_main_1.c src/main/u_main_2.c \
	src/main/header.c src/signals/signals.c src/parser/parser.c \
	src/lexer/l_utils_one.c src/lexer/l_utils_two.c \
	src/lexer/l_utils_three.c src/lexer/l_utils_four.c\
	src/lexer/lexer.c src/parser/p_utils_one.c \
	src/parser/p_utils_two.c src/parser/p_utils_three.c \
	src/executor/builtins_1.c src/executor/builtins_2.c \
	src/executor/u_builtins_two.c \
	src/executor/executor.c src/executor/u_cleanup.c \
	src/executor/u_env_vars.c src/executor/u_cd_cmd.c\
	src/executor/u_exec_file_search.c src/executor/u_executor_1.c \
	src/executor/u_executor_2.c src/executor/u_executor_3.c \
	src/executor/u_exit_cmd.c src/executor/u_echo_cmd.c \
	src/executor/u_export_cmd_1.c src/executor/u_export_cmd_2.c \
	src/executor/u_proc_and_pipes.c src/executor/u_unset_cmd.c \
	src/executor/u_wait_for_proc.c \
	src/expander/e_utils_one.c src/expander/expander.c \

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
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) \
	-lft -lreadline > /dev/null
	@echo "$(GREEN)Executable $(NAME) created successfully!$(RESET)"

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@echo "$(GREEN)Library libft created successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $< > /dev/null

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