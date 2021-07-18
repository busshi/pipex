# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 14:19:45 by aldubar           #+#    #+#              #
#    Updated: 2021/07/18 15:21:59 by aldubar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

SRCS			=	main.c init.c path.c exit.c \
				libft_utils.c libft_utils2.c libft_utils3.c

SRCS_BONUS		=	main_bonus.c init_bonus.c path_utils_bonus.c exit_bonus.c \
				libft_utils_bonus.c libft_utils2_bonus.c libft_utils3_bonus.c

CC			=	@clang

CFLAGS			=	-Wall -Wextra -Werror

RM			=	@rm -rf

INC_DIR			=	./includes

OBJS			=	$(addprefix srcs/, $(SRCS:.c=.o))

OBJS_BONUS		=	$(addprefix bonus/, $(SRCS_BONUS:.c=.o))

OK			=	"\r[ \033[0;32mok\033[0m ]"


.c.o:
		$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(INC_DIR)/pipex.h
		@echo "[....] Compiling $(NAME)\c"
		$(CC) $(CFLAGS) $(OBJS) -o $@
		@echo $(OK)

all:		$(NAME)

bonus:		$(OBJS_BONUS) $(INC_DIR)/pipex_bonus.h
		@echo "[....] Compiling $(NAME)\c"
		$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)
		@echo $(OK)

clean:
		@echo "[....] Removing $(NAME) objects\c"
		$(RM) $(OBJS) $(OBJS_BONUS)
		@echo $(OK)

fclean:		clean
		@echo "[....] Removing $(NAME)\c"
		$(RM) $(NAME)
		@echo $(OK)

check:		fclean
		@if [ ! -d pipex_checker ]; then git clone https://github.com/busshi/pipex_checker.git; fi
		@cd pipex_checker && /bin/bash pipex_checker.sh

re:		fclean all

.PHONY:		all run clean fclean re check
