# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafioron <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 15:31:44 by mafioron          #+#    #+#              #
#    Updated: 2024/11/14 20:05:25 by mafioron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# names
NAME = fdf
#BONUS_NAME = checker
LIBFT = full_libft/libftfull.a

# Compilation
CC = gcc
MAKEFLAGS += --silent
WFLAGS = -Wall -Werror -Wextra
CFLAGS += -O3 -I$(INCS_DIR) -I$(LIBFT_INC) -I/usr/include -I$(MLX_DIR) -g3

# Libraries
MLX_DIR = minilibx-linux/
MLX = $(MLX_DIR)libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

#printing
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m
CLEAR = \033[2K\r

# source and include directories
SRCS_DIR = src/
SRCS_BONUS_DIR = src/checker_bonus/
INCS_DIR = include/
LIBFT_INC = full_libft/include/

#sources
COMMON_SRC = fdf.c draw.c draw_utils.c window.c \
			 parsing/parsing.c \
			 parsing/parsing_utils.c \
			 parsing/parsing2.c

#MAIN_SRC =

#SRC_BONUS = 

# full src with prefix
COMMON_SRCS = $(addprefix $(SRCS_DIR), $(COMMON_SRC))
#MAIN_SRCS = $(addprefix $(SRCS_DIR), $(MAIN_SRC))
#SRCS_BONUS = $(addprefix $(SRCS_BONUS_DIR), $(SRC_BONUS))

# src to obj convertion
COMMON_OBJ = $(COMMON_SRCS:.c=.o)
#MAIN_OBJ = $(MAIN_SRCS:.c=.o)
#OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C full_libft re

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX) $(COMMON_OBJ)
	@printf "$(CLEAR)$(YELLOW)Creating $(NAME)..."
	@$(CC) $(COMMON_OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@printf "$(CLEAR)$(GREEN)✓ $(NAME) successfully created!\n"

#bonus: $(LIBFT) $(COMMON_OBJ) $(OBJ_BONUS)
#	$(CC) -o $(BONUS_NAME) $(COMMON_OBJ) $(OBJ_BONUS) $(LIBFT)

clean:
	@printf "$(CLEAR)$(YELLOW)Cleaning object files..."
	@$(MAKE) -C full_libft clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -f $(COMMON_OBJ)
	@printf "$(CLEAR)$(GREEN)✓ Object files cleaned!\n"

fclean: clean
	@printf "$(CLEAR)$(YELLOW)Removing executables..."
	@$(MAKE) -C full_libft fclean
	@rm -f $(NAME)
	@printf "$(CLEAR)$(GREEN)✓ Executables removed!\n"

re: fclean all

.PHONY: all clean fclean re bonus
