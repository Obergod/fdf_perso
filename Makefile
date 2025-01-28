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
WFLAGS = -Wall -Werror -Wextra
CFLAGS += -O3 -I$(INCS_DIR) -I$(LIBFT_INC) -I/usr/include -I$(MLX_DIR) -g3

# Libraries
MLX_DIR = minilibx-linux/
MLX = $(MLX_DIR)libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# source and include directories
SRCS_DIR = src/
SRCS_BONUS_DIR = src/checker_bonus/
INCS_DIR = include/
LIBFT_INC = full_libft/include/

#sources
COMMON_SRC = fdf.c draw.c \
			 parsing/parsing.c

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
	$(CC) $(COMMON_OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

#bonus: $(LIBFT) $(COMMON_OBJ) $(OBJ_BONUS)
#	$(CC) -o $(BONUS_NAME) $(COMMON_OBJ) $(OBJ_BONUS) $(LIBFT)

clean:
	$(MAKE) -C full_libft clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(COMMON_OBJ)

fclean: clean
	$(MAKE) -C full_libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
