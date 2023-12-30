SRC_DIR := src
LIBFT_DIR := libft
OBJ_DIR := obj

SRC = 	00_main.c \
		01_lexer.c \
		02_token.c \
		03_token_list.c \
		04_syntax.c \
		05_parsing.c \
		06_parsing_utils.c \
		07_exec.c \
		08_exec2.c \
		09_exec_utils.c \
		10_builtins.c \
		11_here_doc.c \
		12_redirection.c \
		13_signal.c \
		14_tokenization.c \
		15_parsing_utils.c \
		16_error.c \
		17_free.c \
		18_unset.c \
		19_cd.c \
		20_pwd.c \
		21_env.c \
		22_set_env.c \
		23_export.c \
		24_export_utils.c \
		25_exit.c \
		26_expand_cmd.c \
		27_expand.c \
		28_expand_utils.c \
		29_exp_utils.c \
		30_expand_line.c \
		31_expand_line_utils.c \
		32_echo.c \
		33_utils.c

SRC        := $(SRC:%=$(SRC_DIR)/%)
OBJ        := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES_LIB += -I $(LIB_FOLDER)/include/


NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -ggdb

RM = rm -f


MAKEFLAGS   += --no-print-directory

DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(OBJ) -lreadline -L./libft -l:libft.a -o $(NAME)
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
		$(RM) -r $(OBJ_DIR)
		@$(MAKE) -C ./libft clean

fclean:	clean
		$(RM) $(NAME)
		@$(MAKE) -C ./libft fclean

re:		fclean all

.PHONY: all clean fclean re
.SILENT:
