# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 19:32:00 by jarregui          #+#    #+#              #
#    Updated: 2024/08/08 11:29:33 by jarregui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# INCLUDE COLOR VARIABLES DECLARATION:
include libs/colors.mk

# VARIABLES DECLARATION:
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
PROY_NAME =	MINITALK
EXEC_FILE_SERVER_NAME = server
EXEC_FILE_CLIENT_NAME = client
EXEC_FILE_SERVER_NAME_BONUS = server_bonus
EXEC_FILE_CLIENT_NAME_BONUS = client_bonus
RM = rm -f

#LIBRARIES
LIBFT_DIR = libs/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
PRINTF_DIR = libs/printf
PRINTF_LIB = $(PRINTF_DIR)/printf.a

# SOURCES
SRCS 	= srcs/server.c \
		srcs/client.c
SRCS_BONUS 	= srcs/server_bonus.c \
		srcs/client_bonus.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
LIBS = ${LIBFT_LIB} ${PRINTF_LIB}

# RULES DECLARATION:
all: subsystems server client

# CREACION ARCHIVOS OBJETO
%.o : %.c
	@echo "${ORANGE}${PROY_NAME} compiling file: $(BROWN)[$<]...${DEF_COLOR}"
	@$(CC) $(CFLAGS) -c -o $@ $< 

subsystems:
# Do Make only if there are changes in the libraries:
	@if [ -f $(LIBFT_LIB) ]; then \
	if find $(LIBFT_DIR) -name "*.c" -newer $(LIBFT_LIB) | grep -q .; then \
	${MAKE} -C $(LIBFT_DIR) all; \
	fi; \
	else \
	${MAKE} -C $(LIBFT_DIR) all; \
	fi

	@if [ -f $(PRINTF_LIB) ]; then \
	if find $(PRINTF_DIR) -name "*.c" -newer $(PRINTF_LIB) | grep -q .; then \
	${MAKE} -C $(PRINTF_DIR) all; \
	fi; \
	else \
	${MAKE} -C $(PRINTF_DIR) all; \
	fi

server: srcs/server.o $(LIBS)
	@$(CC) ${CFLAGS} srcs/server.o ${LIBS} -o $(EXEC_FILE_SERVER_NAME)
	@echo "$(GREEN)✓ Created Server File$(DEF_COLOR)\n"

server_bonus: srcs/server_bonus.o $(LIBS)
	@$(CC) ${CFLAGS} srcs/server_bonus.o ${LIBS} -o $(EXEC_FILE_SERVER_NAME_BONUS)
	@echo "$(GREEN)✓ Created Server File BONUS$(DEF_COLOR)\n"

client: srcs/client.o $(LIBS)
	@$(CC) ${CFLAGS} srcs/client.o ${LIBS} -o $(EXEC_FILE_CLIENT_NAME)
	@echo "$(GREEN)✓ Created Cliente File$(DEF_COLOR)\n"

client_bonus: srcs/client_bonus.o $(LIBS)
	@$(CC) ${CFLAGS} srcs/client_bonus.o ${LIBS} -o $(EXEC_FILE_CLIENT_NAME_BONUS)
	@echo "$(GREEN)✓ Created Cliente File BONUS$(DEF_COLOR)\n"

bonus: subsystems server_bonus client_bonus

clean:
	@${RM} ${OBJS} ${OBJS_BONUS}
	@echo "\n$(GREEN)✓ All objects from ${PROY_NAME} cleaned successfully$(DEF_COLOR)"
	@echo "$(GREEN)Note: run $(YELLOW)make cleanlibs$(GREEN) if also want to clean all libraries $(DEF_COLOR)\n"

cleanlibs: 
	@${MAKE} -C $(LIBFT_DIR) clean
	@${MAKE} -C $(PRINTF_DIR) clean

fclean: clean
	@${RM} ${EXEC_FILE_SERVER_NAME} ${EXEC_FILE_CLIENT_NAME} ${EXEC_FILE_SERVER_NAME_BONUS} ${EXEC_FILE_CLIENT_NAME_BONUS}
	@echo "\n$(GREEN)✓ All executable from ${PROY_NAME} cleaned successfully $(DEF_COLOR)"
	@echo "$(GREEN)Note: run $(YELLOW)make fcleanlibs$(GREEN) if also want to fclean all libraries $(DEF_COLOR)\n"

fcleanlibs: 
	@${MAKE} -C $(LIBFT_DIR) fclean
	@${MAKE} -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all bonus clean cleanlibs fclean fcleanlibs re
