# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmole <mmole@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/28 17:04:02 by mmole             #+#    #+#              #
#    Updated: 2015/01/28 17:04:05 by mmole            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=		main.c envlist.c ft_build_env.c ft_build_setenv.c \
				ft_build_unsetenv.c ft_execute.c ft_core.c
			
OBJ		=		$(SRC:.c=.o)

LIB		=		libft/libft.a

INC		=		libft/includes

NAME	=		ft_minishell1

RM		=		rm -f

FLAG	=		-Wall -Werror -Wextra -g

all: libft.a $(NAME)

$(NAME): $(OBJ)
		gcc $(FLAG) -o $(NAME) $(OBJ) -L. $(LIB)

%.o:		%.c
		gcc $(FLAG) -c $^ -o $@ -I $(INC)

libft.a:
		make -C libft/

re:		fclean all

clean:
		@$(RM) $(OBJ)
		make -C libft/ clean

fclean: clean
		@$(RM) $(NAME)
		make -C libft/ fclean
		@$(RM) libft.h.gch

.PHONY: all clean fclean re
