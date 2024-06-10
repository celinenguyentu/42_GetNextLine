NAME		=	gnl
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
VFLAGS		=	-g3

MSRCS		=	mandatory_tests.c \
				../get_next_line.c \
				../get_next_line_utils.c
BSRCS		=	bonus_tests.c \
				../get_next_line_bonus.c \
				../get_next_line_utils_bonus.c

MOFILES		=	${MSRCS:.c=.o}
BOFILES		=	${BSRCS:.c=.o}

all:		${NAME}

${NAME}:	${MOFILES}
			@${CC} ${CFLAGS} ${VFLAGS} ${OPTION} ${MOFILES} -o ${NAME}

bonus:		${BOFILES}
			@${CC} ${CFLAGS} ${VFLAGS} ${OPTION} ${BOFILES} -o ${NAME}

.c.o: 
	@${CC} ${CFLAGS} ${OPTION} -c $< -o $@

clean:
	rm -rf ${MOFILES} ${BOFILES} 

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
