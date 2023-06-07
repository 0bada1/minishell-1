# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 11:29:51 by ooutabac          #+#    #+#              #
#    Updated: 2023/06/07 20:23:09 by ooutabac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIBFT_DIR	=	libft
LIBFT		=	libft.a
RL_INC		=	-I /usr/local/opt/readline/include #-I /goinfre/include
RL_LINK		=	-L /usr/local/opt/readline/lib -l readline #-L /goinfre/lib -l readline

INC_DIR		=	include
SRC_DIR		=	src
OBJ_DIR		=	objects

SRCS		=	parsing/check_validity1.c		\
				parsing/check_validity2.c		\
				parsing/count_redirections.c	\
				parsing/dollar_sign1.c			\
				parsing/dollar_sign2.c			\
				parsing/dollar_sign3.c			\
				parsing/dollar_sign4.c			\
				parsing/dollar_sign5.c			\
				parsing/dollar_sign6.c			\
				parsing/dollar_sign7.c			\
				parsing/dollar_sign8.c			\
				parsing/free.c					\
				parsing/get_commands.c			\
				parsing/get_env_struct.c		\
				parsing/get_exec_struct.c		\
				parsing/get_files1.c			\
				parsing/get_files2.c			\
				parsing/get_flags.c				\
				parsing/length_to_pipe.c		\
				parsing/lexer1.c				\
				parsing/lexer2.c				\
				parsing/num_tokens.c			\
				parsing/parse.c					\
				parsing/raw_lexer1.c			\
				parsing/raw_lexer2.c			\
				parsing/skip1.c					\
				parsing/skip2.c					\
				parsing/split_command_block.c	\
				parsing/split_pipes.c			\
				parsing/token_size.c			\
				src/main.c						\
				builtin/echo.c					\
				builtin/env.c					\
				builtin/pwd.c					\
				builtin/unset.c					\
				builtin/exit.c					\
				builtin/export.c				\
				builtin/cd.c					\
				builtin/builtin_utils.c			\
				src/excution.c					\
				src/exec_child.c				\
				src/redir.c						\
				src/exec_heredoc.c				\
				src/exec_infile.c				\
				src/exec_outfile.c				\
				src/pipes.c						\
				src/signal.c					\

OBJS		=	$(SRCS:%c=%o)

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g3
RM			=	rm -rf

all:		$(NAME)
	@echo "           ████"
	@echo "         ▒▒▓▓▓▓▒▒"
	@echo "           ▓▓▓▓░░"
	@echo "           ▓▓▓▓                    ░░"
	@echo "     ▓▓████████████                ░░"
	@echo "     ░░██████████▓▓            ░░░░░░░░░░"
	@echo "       ▓▓████████▓▓            ░░░░░░░░░░            ▒▒"
	@echo "       ▒▒████████              ░░░░░░░░              ▓▓░░"
	@echo "         ██▓▓████                ░░░░░░              ▓▓  ▒▒            ░░░░"
	@echo "     ░░▓▓▓▓▓▓▓▓▓▓▒▒              ░░░░░░            ██▓▓▒▒▓▓          ░░░░░░░░            ▒▒▓▓▓▓▓▓▓▓▓▓▓▓"
	@echo "       ▒▒████████▒▒            ░░░░░░░░░░          ██▓▓▓▓██        ░░░░░░░░░░░░          ▓▓▓▓▓▓████▓▓▓▓"
	@echo "         ████████                ▒▒▒▒▒▒            ▓▓██████        ░░░░░░░░░░░░░░░░      ░░▓▓▓▓██▓▓▓▓▒▒              ░░"
	@echo "         ████████                ░░░░░░            ▒▒████▓▓        ░░░░░░░░░░░░░░░░        ██████████            ░░░░░░░░"
	@echo "         ██▓▓████                ░░░░░░            ░░▓▓██▓▓        ░░░░░░░░░░░░░░░░░░      ██▓▓██████            ░░░░░░░░░░"
	@echo "         ██▓▓████                ░░░░░░            ▓▓▓▓▓▓▓▓        ░░░░░░░░░░    ░░░░      ██████████            ░░░░░░░░░░"
	@echo "         ██▓▓▓▓██                ░░░░░░            ░░████▒▒        ░░░░░░░░░░░░            ██████████            ░░▒▒░░░░░░"
	@echo "         ██▓▓▓▓▓▓                ░░░░░░              ██████          ░░░░░░░░░░░░          ██████████            ░░░░░░░░░░"
	@echo "       ░░▓▓▓▓▓▓▓▓                ░░░░░░              ████            ░░░░░░░░░░░░░░        ██████████              ▒▒▒▒▒▒"
	@echo "       ██▓▓▓▓▓▓▓▓                ░░░░░░░░            ▓▓▓▓            ░░░░░░░░░░░░░░        ██████████              ░░░░░░"
	@echo "       ██▓▓▓▓▓▓▓▓              ░░░░░░░░░░            ▓▓██▓▓        ░░░░░░░░░░░░░░░░        ██████████              ░░░░░░"
	@echo "       ██▓▓▓▓▓▓▓▓██            ░░░░░░░░░░          ░░▓▓▓▓▓▓          ░░░░░░░░░░░░░░      ░░██▓▓██▓▓██░░          ░░░░░░░░"
	@echo "     ▓▓▓▓▓▓▓▓▓▓▓▓██▒▒        ░░░░░░░░░░░░░░        ▓▓▓▓▓▓▓▓▒▒          ░░░░░░░░░░        ▓▓▓▓▓▓██▓▓▓▓██          ░░░░░░░░░░"
	@echo " ▓▓██▓▓██████████▓▓▓▓▓▓    ░░░░░░░░░░░░░░░░░░    ░░██▓▓████▓▓▒▒      ░░░░░░░░░░░░░░    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▒▒      ░░░░░░░░░░░░░░"
	@echo " ██████████████████████░░  ░░░░░░░░░░░░░░░░▒▒    ██▓▓▓▓██▓▓▓▓██    ░░░░░░▒▒▒▒▒▒▒▒░░    ████████████▓▓██▓▓    ▒▒░░░░░░░░░░░░░░░░"
	@echo "▒████▓▓▓▓▓▓████▓▓▓▓████▒▒░░▒▒░░░░░░░░░░░░░░▒▒░░░░██▓▓▓▓██▓▓██▓▓▒▒░░▒▒░░░░░░░░░░░░░░░░░░██▓▓▓▓▓▓▓▓████▓▓▓▓░░░░▒▒░░░░░░░░░░░░░░░░░░"

%.o : %.c
# @mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) $(RL_INC) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(RL_LINK) -o $@

$(LIBFT):
			@make -C $(LIBFT_DIR) all
			@make -C $(LIBFT_DIR) bonus

clean:
		@make -C $(LIBFT_DIR) fclean
	$(RM) ./*/*.o
# $(RM) ./src/*.o
# $(RM) ./parsing/*.o
# $(RM) ./builtin/*.o


# @make -C $(GNL_DIR) fclean
			@$(RM) $(OBJ_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

mem:
	valgrind -s --track-fds=yes --tool=memcheck --leak-check=full --show-leak-kinds=all --suppressions=.ignore_readline ./minishell
