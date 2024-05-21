NAME		=	gnl

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

MSRCS		=	mandatory_tests.c \
				../get_next_line.c \
				../get_next_line_utils.c

MOFILES		=	${MSRCS:.c=.o}

BSRCS		=	bonus_tests.c \
				../get_next_line_bonus.c \
				../get_next_line_utils_bonus.c

BOFILES		=	${BSRCS:.c=.o}

all:		${NAME}

${NAME}:	${MOFILES}
			@${CC} ${CFLAGS} ${OPTION} ${MOFILES} -o ${NAME} -g

bonus:		${BOFILES}
			@${CC} ${CFLAGS} ${OPTION} ${BOFILES} -o ${NAME} -g

.c.o: 
	@${CC} ${CFLAGS} ${OPTION} -c $< -o $@

clean:
	rm -rf ${MOFILES} ${BOFILES} 

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
