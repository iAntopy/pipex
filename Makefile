
SRC_DIR		= src/

SRC		=	pipex_main.c \
			get_here_doc_input.c \
			exec_cmds.c \
			validater_funcs.c \
			substr_substitution.c

SRC_BASE	= $(addprefix $(SRC_DIR), $(SRC))

SRC_M		= $(SRC_DIR)error_handling_man.c
SRC_B		= $(SRC_DIR)error_handling_bns.c

OBJ_BASE	= $(SRC_BASE:.c=.o)
OBJ_M		= $(SRC_M:.c=.o)
OBJ_B		= $(SRC_B:.c=.o)
#OBJS		= $(OBJS_M) $(OBJS_B)

INCLS		= includes/

LIBS_DIR	= libs/
_LIBS		= libft.a
LIBS		= $(addprefix $(LIBS_DIR), $(_LIBS))

#$(OBJS_M):	DEF_CMD_MAX := -D CMD_MAX=2
#$(OBJS_B):	DEF_CMD_MAX := -D CMD_MAX=128

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror

NAME		= pipex
NAME_BONUS	= pipex_bonus

$(NAME):	build_libs $(OBJ_BASE) $(OBJ_M)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BASE) $(OBJ_M) $(LIBS)

$(NAME_BONUS):	build_libs $(OBJ_BASE) $(OBJ_B)
		$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BASE) $(OBJ_B) $(LIBS)

all:		$(NAME)

bonus:		$(NAME_BONUS)


$(OBJ_BASE):	%.o : %.c
		-$(CC) $(CFLAGS) -D CMD_MAX=128 -I$(INCLS) -c $< -o $@
$(OBJ_M):	%.o : %.c
		-$(CC) $(CFLAGS) -D CMD_MAX=2 -I$(INCLS) -c $< -o $@
$(OBJ_B):	%.o : %.c
		-$(CC) $(CFLAGS) -D CMD_MAX=128 -I$(INCLS) -c $< -o $@
#$(OBJS)	:	%o : %c
#		-$(CC) $(CFLAGS) $(DEF_CMD_MAX) -I$(INCLS) -c $< -o $@
#%.o:		%.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=2 -I$(INCLS) -c $< -o $@
#%.bo:		%.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=128 -I$(INCLS) -c $< -o $@
#$(OBJS_M):		%.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=2 -I$(INCLS) -c $< -o $@
#%.bo:		%.c
#		-$(CC) $(CFLAGS) -D CMD_MAX=128 -I$(INCLS) -c $< -o $@

build_libs:
	make -C $(LIBS_DIR)libft extra
	cp $(LIBS_DIR)libft/libft.a $(LIBS_DIR)

clean:
		rm -f $(OBJ_BASE) $(OBJ_B) $(OBJ_M) $(LIBS)

fclean:		clean
		rm -f $(NAME)

re:			fclean all

#bonus:		$(NAME) $(OBJS_B)
#			$(AR) $(NAME) $(OBJS_B)
