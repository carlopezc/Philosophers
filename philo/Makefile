# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlotalcd <carlotalcd@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 12:23:06 by carlopez          #+#    #+#              #
#    Updated: 2025/08/07 22:12:23 by carlotalcd       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CCFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
NAME = philo

AR = ar
ARFLAGS = rcs

LIB = ft_philosophers.h
MAIN = ft_main.c

#COLOURS AND TEXT FORMAT
LIGHT_YELLOW	= \033[1;33m
BOLD_GREEN    = \033[1;32m
BOLD_PURPLE   = \033[1;35m
BOLD_CYAN     = \033[1;36m
PINK_LIGHT= \033[38;5;217m
RED_BRIGHT     = \033[38;2;255;0;0m
PINK_FUCHSIA    = \033[38;2;255;20;147m

RESET  = \033[0m

SRC = ft_utils.c ft_actions.c ft_check.c ft_init.c ft_time.c
OBJ = $(SRC:.c=.o)

all: 
	@echo "$(PINK_FUCHSIA)\n MAKING PHILOSOPHERS\n$(RESET)"
	@$(MAKE) --no-print-directory $(NAME)

$(NAME): $(MAIN) $(OBJ) $(PRINTF)
	@echo "$(BOLD_CYAN)\nCompiling program...$(RESET)"
	$(CC) $(CCFLAGS)  -lpthread $(MAIN) $(OBJ) $(PRINTF) -o $(NAME)
	@echo "$(BOLD_CYAN)\n!Compilation completed, $(LIGHT_YELLOW)philosophers💭$(BOLD_CYAN) ready to be used!\n$(RESET)"

%.o: %.c $(LIB) Makefile
	@echo "$(PINK_LIGHT)🡲 Creating object...$(RESET)"
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@echo "$(RED_BRIGHT)\nThrowing object files of philosopheres to 🗑️$(RESET)"
	rm -f $(OBJ) $(OBJ_BONUS)
	@echo "$(RED_BRIGHT)\nThrowing object files of philosophers to 🗑️$(RESET)"
	rm -f $(PRINTFDIR)/*.o

fclean: clean
	@echo "$(RED_BRIGHT)\nDestroying program 💥$(RESET)"
	rm -f $(NAME) checker
	@echo "\n$(BOLD_GREEN) Bye bye 👋 $(RESET)\n" 

re: fclean all

.PHONY: all clean fclean re bonus