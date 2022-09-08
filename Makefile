
SRC_DIR		= src/

_SRC	=	pipex_main \
			validator_funcs \
			substr_substitution \
			error_handling	\
			get_here_doc_input

SRC			= $(addprefix $(SRC_DIR), $(_SRC))

#_SRC_M		= $(SRC) error_handling_man.c
#_SRC_B		= $(SRC) error_handling_bns.c

SRC_M		= $(addsuffix .c, $(SRC))
SRC_B		= $(addsuffix _bonus.c, $(SRC))

OBJ_M		= $(SRC_M:.c=.o)
OBJ_B		= $(SRC_B:.c=.o)

INCLS		= includes/

LIBFT		= libft/libft.a

$(OBJ_M):	DEF_CMD_MAX := -D CMD_MAX=2
$(OBJ_B):	DEF_CMD_MAX := -D CMD_MAX=128

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror

NAME		= pipex
NAME_BONUS	= pipex_bonus

%.o:		%.c
		-$(CC) $(CFLAGS) $(DEF_CMD_MAX) -I$(INCLS) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJ_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M) $(LIBFT)

$(NAME_BONUS):	$(LIBFT) $(OBJ_B)
		$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_B) $(LIBFT)

$(LIBFT):
		make -C libft/

all:		$(NAME)

bonus:		$(NAME_BONUS)

clean:
		rm -f $(OBJ_B) $(OBJ_M) $(LIBS)

fclean:		clean
		rm -f $(NAME)

re:			fclean all
