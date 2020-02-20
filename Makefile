# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/23 21:42:39 by jchotel           #+#    #+#              #
#    Updated: 2020/01/24 01:40:43 by jchotel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSC		=	srcs/action.c\
				srcs/init.c\
				libs/libft/ft_putstr.c\
				libs/libft/ft_split.c\
				libs/libft/ft_strcmp.c\
				libs/libft/ft_atoi.c\
				libs/libft/ft_isdigit.c\
				libs/libft/ft_strjoin.c\
				libs/libft/ft_isascii.c\
				libs/libft/ft_strlen.c\
				libs/libft/ft_strcpy.c\
				libs/libft/ft_strdup.c\
				libs/libft/ft_strncmp.c\
				libs/libft/ft_strnstr.c\
				libs/libft/ft_strchr.c\
				libs/libft/ft_stronly.c\
				libs/libft/ft_calloc.c\
				libs/libft/ft_lstadd_front.c\
				libs/libft/ft_lstadd_back.c\
				libs/libft/ft_lstclear.c\
				libs/libft/ft_lstdelone.c\
				libs/libft/ft_lstiter.c\
				libs/libft/ft_lstlast.c\
				libs/libft/ft_itoa.c\
				libs/libft/ft_lstmap.c\
				libs/libft/ft_lstnew.c\
				libs/libft/ft_bzero.c\
				libs/libft/ft_lstrev.c\
				libs/libft/ft_lstsize.c\

SRCSH		= includes/philo.h
OBJS		= $(SRCSC:%.c=%.o)
NAME		= philo.a
CC			= gcc
AR			= ar rc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror

.c.o: ${OBJS}
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@echo "\033[1;32m"
			@echo "┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐"
			@echo "└─┐│ ││  │  ├┤ └─┐└─┐"
			@echo "└─┘└─┘└─┘└─┘└─┘└─┘└─┘"
			@echo "philo.a generated successfully.\033[0;0m"
			@${AR} ${NAME} ${OBJS} ${SRCSH}

all:		${NAME}

clean:
			@echo "Deleting .o files.."
			@${RM} ${OBJS}

fclean:		clean
			@echo "Deleting binary files.."
			@${RM} ${NAME}

re:			fclean all

test-a:		all
			@${CC} -g -fsanitize=address ${NAME} ${LIBFT} ./main.c -o philo
			@make clean
			@./philo 6

test:		all
			${CC} ${NAME} ${CFLAGS} ${LIBFT} ./main.c -o philo
			@make clean
			@./philo

.PHONY:		all clean fclean re