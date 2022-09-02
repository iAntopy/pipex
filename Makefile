#SRCS_M		= $(addsuffix $(SUF_M), $(SRCS_TEMP_M))
#SRCS_B		= $(addsuffix $(SUF_M), $(SRCS_TEMP_B))
SRCS_M		= $(wildcard src/*.c)

OBJS_M		= $(SRCS_M:.c=.o)

INCLS		= includes/

LIBS_DIR	= libs/
_LIBS		= libft.a
LIBS		= $(addprefix $(LIBS_DIR), $(_LIBS))

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror

NAME		= Pipex
NAME_BONUS	= Pipex_bonus

.c.o:
		-$(CC) $(CFLAGS) -I$(INCLS) -c $< -o $(<:.c=.o)

$(NAME):	build_libs $(OBJS_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS_M) $(LIBS)

$(NAME_BONUS):	build_libs $(OBJS_M)
		$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_M) $(LIBS)

all:		$(NAME)

bonus:		$(NAME_BONUS)

build_libs:
	make -C $(LIBS_DIR)libft extra
	cp $(LIBS_DIR)libft/libft.a $(LIBS_DIR)

clean:
		rm -f $(OBJS_M)

fclean:		clean
		rm -f $(NAME)

re:			fclean all

#bonus:		$(NAME) $(OBJS_B)
#			$(AR) $(NAME) $(OBJS_B)
