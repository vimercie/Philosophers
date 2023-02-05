NAME=		philo

VPATH=		src/

OBJDIR=		obj

INCDIR=		inc

SRC=		main.c						\
			parsing.c					\
			threading.c					\
			init.c						\
			philo_utils.c				\
			libft_func.c				\
			checking.c



OBJ=		${addprefix ${OBJDIR}/,		\
			${SRC:.c=.o}}

INC=		${INCDIR}/philo.h

CC=			gcc

CFLAGS=		-Wall -Wextra -Werror

all:		${OBJDIR} ${NAME}

${NAME}:	${OBJ} ${INC}
			${CC} ${OBJ} -o ${NAME} -lpthread

${OBJDIR}:
			mkdir -p obj

${OBJDIR}/%.o:	%.c ${INC} Makefile
			${CC} ${CFLAGS} -c $< -o $@


clean:
			rm -rf ${OBJDIR}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re