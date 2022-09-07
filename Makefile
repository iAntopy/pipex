
SRC_DIR		= src/

SRC		=	pipex_main.c \
			exec_cmds.c \
			validater_funcs.c \
			substr_substitution.c \
			get_here_doc_input.c

#SRC_BASE	= $(addprefix $(SRC_DIR), $(SRC))

_SRC_M		= $(SRC) error_handling_man.c
_SRC_B		= $(SRC) error_handling_bns.c

SRC_M		= $(addprefix $(SRC_DIR), $(_SRC_M))
SRC_B		= $(addprefix $(SRC_DIR), $(_SRC_B))

OBJ_M		= $(SRC_M:.c=.mo)
OBJ_B		= $(SRC_B:.c=.bo)
#OBJS		= $(OBJS_M) $(OBJS_B)

INCLS		= includes/

LIBS_DIR	= libs/
_LIBFT		= libft.a
LIBFT		= $(addprefix $(LIBS_DIR), $(_LIBFT))

#$(OBJ_M):	DEF_CMD_MAX := -D CMD_MAX=2
#$(OBJ_B):	DEF_CMD_MAX := -D CMD_MAX=128

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror

NAME		= pipex
NAME_BONUS	= pipex_bonus

#%.o:		%.c
#		-$(CC) $(CFLAGS) $(DEF_CMD_MAX) -I$(INCLS) -c $< -o $@
%.mo : %.c
		-$(CC) $(CFLAGS) -D CMD_MAX=2 -I$(INCLS) -c $< -o $@
%.bo : %.c
		-$(CC) $(CFLAGS) -D CMD_MAX=128 -I$(INCLS) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJ_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M) $(LIBFT)

$(NAME_BONUS):	$(LIBFT) $(OBJ_B)
		$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_B) $(LIBFT)

$(LIBFT):
		make -C libft/

all:		$(NAME)

bonus:		$(NAME_BONUS)

#$(OBJ_BASE):	%.o : %.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=128 -I$(INCLS) -c $< -o $@
#%.mo : %.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=2 -I$(INCLS) -c $< -o $@
#%.bo : %.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=128 -I$(INCLS) -c $< -o $@
#$(OBJS)	:	%o : %c
#		-$(CC) $(CFLAGS) $(DEF_CMD_MAX) -I$(INCLS) -c $< -o $@
#%.o:		%.c
#		-$(CC) $(CFLAGS) $(DEF_CMD_MAX) -I$(INCLS) -c $< -o $@
#%.bo:		%.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=128 -I$(INCLS) -c $< -o $@
#$(OBJS_M):		%.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=2 -I$(INCLS) -c $< -o $@
#%.bo:		%.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=128 -I$(INCLS) -c $< -o $@

build_libs:
	make -C libft

clean:
		rm -f $(OBJ_B) $(OBJ_M) $(LIBS)

fclean:		clean
		rm -f $(NAME)

re:			fclean all
