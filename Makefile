SRCS_SERV	= server.c\
				ft_printf/ft_printf.c\
				ft_printf/ft_print_chars.c\
				ft_printf/ft_print_numbs.c
SRCS_CLIENT	= client.c\
				ft_printf/ft_printf.c\
				ft_printf/ft_print_chars.c\
				ft_printf/ft_print_numbs.c\
				funcs.c
INC		= minitalk.h

CC			= cc
CFLAGS	= -Werror -Wextra -Wall

all:		server client

%.o:%.c
	cc -Werror -Wall -Wextra -o $@ -c $<

server:		${SRCS_SERV:.c=.o}
			${CC} $(CFLAGS) ${SRCS_SERV} -o server -I ${INC}

client:		${SRCS_CLIENT:.c=.o}
			${CC} $(CFLAGS) ${SRCS_CLIENT} -o client -I ${INC}

clean:
			rm -f ${SRCS_SERV:.c=.o} ${SRCS_CLIENT:.c=.o}

fclean:		clean
			rm -f client server

re:			fclean all

.PHONY:		all clean fclean re