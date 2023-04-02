NAME = minishell
LIB_F = libft
LIB = libft.a
SRC = src
OBJ = obj
INC = inc
CFLAGS = -g -I$(INC) #-fsanitize=address #-Wall -Wextra -Werror
RM = rm -rf
CC = gcc
SRCS =	src/builtins/builtins.c\
		src/builtins/ft_cd.c\
		src/builtins/ft_echo.c\
		src/builtins/ft_env.c\
		src/builtins/ft_exit.c\
		src/builtins/ft_export.c\
		src/builtins/ft_pwd.c\
		src/builtins/ft_unset.c\
		src/builtins/utils_builtins.c\
		src/error/error_handling.c\
		src/error/ft_error.c\
		src/executor/check_redirections.c\
		src/executor/executor_utils.c\
		src/executor/executor.c\
		src/executor/handle_cmd.c\
		src/executor/heredoc.c\
		src/expander/expander.c\
		src/expander/expander_utils.c\
		src/expander/expander_utils2.c\
		src/lexer/handlers.c\
		src/lexer/lexer.c\
		src/lexer/token_reader.c\
		src/parser/handle_redirections.c\
		src/parser/parser_utils.c\
		src/parser/parser.c\
		src/utils/minishell_loop.c\
		src/utils/parse_envp.c\
		src/utils/lexer_clear_utils.c\
		src/utils/lexer_utils.c\
		src/utils/one_cmd_utils.c\
		src/utils/utils.c\
		src/main.c\
		src/signals.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB_F)/$(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_F)/$(LIB) -o $(NAME) -lreadline

$(LIB_F)/$(LIB):
	@make -C $(LIB_F)
	@echo "libft is done!"

clean:
	@$(RM) $(OBJS)
	rm -rf obj 
	@echo "successfuly cleaned"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIB_F)
	@echo "executable removed successfuly"

leaks:
	make
	leaks --atExit -- ./minishell

re: fclean all