FUNC_NAMES_M =	issign isspace isalpha isdigit isalnum isascii		\
		isprint strlen memset bzero memcpy memmove strlcpy	\
		strlcat isupper islower toupper tolower strchr strrchr	\
		strcmp strncmp memchr memcmp strnstr atoi atoi_base itoa\
		calloc strlcat substr strjoin strtrim strdup		\
		split split_set split_space				\
		strmapi striteri					\
		putchar_fd putstr_fd putendl_fd putnbr_fd		\
		pow strlower strupper #atof				

FUNC_NAMES_B =	lstnew lstcreate lstinsert lstadd_front lstadd_back lstsize	\
		lstlast lstdelone lstclear lstiter lstmap lstpop lstmap lstprint

# ft_randint not included because is in same file as ft_random
FUNC_NAMES_EXTRA =	ft_printf ft_vprintf ft_random ft_clamp fperror malloc_free	\
			get_next_line get_next_line_utils ft_deltatime_usec ft_memclear strtab_utils	\
			find_file_in_env

PREF		= ft_
SUF_M		= .c

SRCS_TEMP_M	= ${addprefix ${PREF}, ${FUNC_NAMES_M}}
SRCS_M		= ${addsuffix ${SUF_M}, ${SRCS_TEMP_M}}

SRCS_TEMP_B	= ${addprefix ${PREF}, ${FUNC_NAMES_B}}
SRCS_B		= ${addsuffix ${SUF_M}, ${SRCS_TEMP_B}}

SRCS_X		= ${addsuffix ${SUF_M}, ${FUNC_NAMES_EXTRA}}

OBJS_M		= ${SRCS_M:.c=.o}
OBJS_B		= ${SRCS_B:.c=.o}
OBJS_X		= ${SRCS_X:.c=.o}

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
			${RM} ${OBJS_M} ${OBJS_B} ${OBJS_X}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:		${NAME} ${OBJS_B}
			${AR} ${NAME} ${OBJS_B}

extra:		${NAME} ${OBJS_X}
			${AR} ${NAME} ${OBJS_X}
