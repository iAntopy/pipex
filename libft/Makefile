FUNC_NAMES_M = isalpha isdigit isalnum isascii isprint strlen memset bzero memcpy memmove strlcpy strlcat toupper tolower strchr strrchr strncmp memchr memcmp strnstr atoi calloc strlcat substr strjoin strtrim split itoa strmapi striteri putchar_fd putstr_fd putendl_fd putnbr_fd strdup

FUNC_NAMES_B = lstnew lstadd_front lstadd_back lstsize lstlast lstdelone lstclear lstiter lstmap

PREF		= ft_
SUF_M		= .c

SRCS_TEMP_M	= ${addprefix ${PREF}, ${FUNC_NAMES_M}}
SRCS_M		= ${addsuffix ${SUF_M}, ${SRCS_TEMP_M}}

SRCS_TEMP_B	= ${addprefix ${PREF}, ${FUNC_NAMES_B}}
SRCS_B		= ${addsuffix ${SUF_M}, ${SRCS_TEMP_B}}

OBJS_M		= ${SRCS_M:.c=.o}
OBJS_B		= ${SRCS_B:.c=.o}

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

AR			= ar -rcs

RM			= rm -f

NAME		= libft.a

.c.o:
			-${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS_M}
			${AR} ${NAME} ${OBJS_M}

all:		${NAME}

clean:
			${RM} ${OBJS_M} ${OBJS_B}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:		${NAME} ${OBJS_B}
			${AR} ${NAME} ${OBJS_B}
