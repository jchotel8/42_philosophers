# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchotel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 11:15:39 by jchotel           #+#    #+#              #
#    Updated: 2020/03/06 16:34:05 by jchotel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL ******************************************************************** #
NAME		= philo_two
LIBS 		= 

# SOURCE ********************************************************************* #			  
SRCS_DIR	= .
SRCS		= 	main.c\
				utils.c\
				init.c\
				routine.c\
				libft_1.c\
				libft_2.c

SRCSH		= philo_two.h
OBJS_DIR	= objs
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

# COMMANDES ****************************************************************** #
FLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
CC			= gcc
AR			= ar rc
RM 			= rm -f
MKDIR		= mkdir

# COLORS ********************************************************************* #
CR			= "\r"$(CLEAR)
CLEAR       = "\\033[0K"
BLACK		= "\033[0;30m"
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
YELLOW		= "\033[1;33m"
DARKBLUE	= "\033[0;34m"
VIOLET		= "\033[0;35m"
BLUE		= "\033[0;36m"

GREY		= "\033[0;2m"
BOLDWHITE	= "\033[0;1m"
WHITE		= "\033[0;0m"

REDB		= "\033[0;41m"

# RULES ********************************************************************** #
all:		${NAME}

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@printf ${CR}"[FILE : %s]" $@
	@${CC} ${FLAGS} -c $< -o $@

$(OBJS_DIR):
			mkdir -p ${OBJS_DIR}

libs:		${SRCSH}
			@printf $(CR)

$(NAME):	libs ${OBJS}
			@${CC} ${FLAGS} ${OBJS} ${LIBS} -lpthread -o ${NAME}
			@echo ${GREEN}${CR}"┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐"
			@echo 		  	   "└─┐│ ││  │  ├┤ └─┐└─┐"
			@echo 		  	   "└─┘└─┘└─┘└─┘└─┘└─┘└─┘"
			@echo ${NAME}" generated successfully." ${WHITE}

bonus:		${NAME}

#run_infinite:
#			@./${NAME} 5 5000 1000 2000

#run_meals:
#			@./${NAME} 5 5000 1000 2000 3

#run_death:
#			@./${NAME} 5 3000 1000 4000

clean:
			@rm -rf ${OBJS} objs
			@echo ${RED}${NAME}" : Removing .o files" ${WHITE}

fclean:		clean
			@rm -f ${NAME}
			@echo ${RED}${NAME}" : Removing binary file" ${WHITE}

re:			fclean all

.PHONY:		all clean fclean re bonus run_infinite run_death run_meals
