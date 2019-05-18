# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/29 18:35:04 by omiroshn          #+#    #+#              #
#    Updated: 2018/06/29 18:35:06 by omiroshn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = clang
FILES = main list merge_sort
LIBFT_DIR = libft/
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_LIST = $(addsuffix .o, $(FILES))
# FLAGS = -Wall -Wextra -Werror -O3
FLAGS = -g
HEADERS = -I./includes -I./libft/includes -I./libft/ft_printf/includes
HEADER = ./includes/ft_ls.h ./includes/colored_str.h

EOC=\033[0m
BLUE=\033[1;34m
YELLOW=\033[1;33m
LGREEN=\033[1;32m
GREEN=\033[32m
RED=\033[31m
LRED=\033[91m
BRED=\033[1;31m

all: $(NAME)

$(NAME): $(LIBFT_DIR)libft.a $(OBJ) $(HEADER)
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIBFT_DIR)libft.a
	@printf " $(RED)>$(EOC) $(GREEN)$(NAME) is ready.$(EOC)\n"
$(LIBFT_DIR)libft.a:
	@make --no-print-directory -j3 -C $(LIBFT_DIR)
$(OBJ): obj/%.o: src/%.c $(HEADER)
	@$(CC) -o $@ $(FLAGS) $(HEADERS) -c $<
	@printf "$(RED).$(EOC)"
clean:
	@rm -f $(OBJ)
	@make --no-print-directory -j3 -C $(LIBFT_DIR) clean
fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory -j3 -C $(LIBFT_DIR) fclean
re: fclean all
