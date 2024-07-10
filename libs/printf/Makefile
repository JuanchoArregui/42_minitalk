# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 13:58:00 by jarregui          #+#    #+#              #
#    Updated: 2024/05/21 12:40:18 by jarregui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# INCLUDE COLOR VARIABLES DECLARATION:
include ../colors.mk

LIB_NAME	=	PRINTF LIBRARY
NAME		=	printf.a

# VARIABLES DECLARATION:
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
# CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
ARFLAGS		=	rcs
RM			=	/bin/rm -f
EXEC_NAME	=	a.out

SRCS		=	$(wildcard functions/*.c)

OBJS		=	${SRCS:.c=.o}

# RULES DECLARATION:
all:		${NAME}

%.o: %.c
	@echo "${ORANGE}${LIB_NAME} compiling file: $(BROWN)[$<]...${DEF_COLOR}"
	@${CC} ${CFLAGS} -c $< -o $@

# CREAMOS BIBLIOTECA ESTATICA Y NO UN EJECUTABLE (NO HAY MAIN)
${NAME}:	${OBJS}
	ar -rc ${NAME} ${OBJS}
	ranlib ${NAME}
	@echo "$(GREEN)✓ Created ${NAME}$(DEF_COLOR)\n"

clean:
	${RM} ${OBJS} ${OBJS_BONUS} ${EXEC_NAME}
	@echo "\n$(GREEN)✓ All objects from ${LIB_NAME} cleaned successfully$(DEF_COLOR)\n"

fclean:		clean
	${RM} ${NAME}
	@echo "\n$(GREEN)✓ All executable from ${LIB_NAME} cleaned successfully $(DEF_COLOR)\n"
 
re:			fclean all

.PHONY:		all clean fclean re bonus