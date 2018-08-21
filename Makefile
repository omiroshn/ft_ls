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
FILES = main
LIBFT_DIR = libft/
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
FLAGS = -Wall -Wextra -Werror -O3
HEADERS = -I./includes -I./libft/includes
HEADER = ./includes/ft_ls.h

all: $(NAME)

$(NAME): $(LIBFT_DIR)libft.a $(OBJ) $(HEADER)
	@echo "\033[36mLinking...\033[0m"
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIBFT_DIR)libft.a
	@echo "\033[32m[ ✔ ] Binary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"
$(LIBFT_DIR)libft.a:
	@make --no-print-directory -j3 -C $(LIBFT_DIR)
$(OBJ): obj/%.o: src/%.c $(HEADER)
	@$(CC) -o $@ $(FLAGS) $(HEADERS) -c $<
	@echo "\033[37mCompilation of \033[97m$(notdir $<) \033[0m\033[37mdone. \033[0m"
clean:
	@rm -f $(OBJ)
	@make --no-print-directory -j3 -C $(LIBFT_DIR) clean
	@echo "\033[31m[ ✔ ] Objects files \033[91m$(OBJ_LIST) \033[0m\033[31m removed. \033[0m"
fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory -j3 -C $(LIBFT_DIR) fclean
	@echo "\033[31m[ ✔ ] Binary \033[1;31m$(NAME) \033[1;0m\033[31mremoved.\033[0m"
re: fclean all
