CC = cc

CFLAGS = -Wall -Wextra -Werror -g

EXEC = minishell

INCLUDES = includes/

SRC = 	srcs/main.c srcs/debug_functions.c srcs/minishell_loop.c srcs/utilities/x_iterate.c srcs/parser/form_comands.c \
		srcs/parser/parser.c srcs/memory/free_commands.c srcs/memory/free_files.c srcs/memory/free_int_split.c srcs/memory/free_string_array.c \
		srcs/memory/free_tokens.c srcs/memory/ft_calloc.c srcs/memory/ft_memcpy.c srcs/masker/mask_dollar_signs.c srcs/masker/mask_pipes.c \
		srcs/masker/mask_quotes.c srcs/masker/mask_redirections.c srcs/masker/mask_white_spaces.c srcs/masker/masker.c srcs/lexer/lexer.c \
		srcs/lexer/syntax_errors.c srcs/lexer/tokenizer.c srcs/ft_type/ft_isalnum.c srcs/ft_type/ft_isalpha.c srcs/ft_type/ft_isdigit.c srcs/ft_type/ft_isspace.c \
		srcs/ft_type/is_operator.c srcs/ft_string/ft_putstr_fd.c srcs/ft_string/ft_strchr.c srcs/ft_string/ft_strcmp.c srcs/ft_string/ft_strdup.c \
		srcs/ft_string/ft_striteri_l.c srcs/ft_string/ft_strlen.c srcs/ft_string/split_int_ptr.c srcs/ft_string/strcpy_to_int.c srcs/expander/expand_heredoc.c \
		srcs/expander/expand_token.c srcs/expander/expander.c srcs/expander/ifs.c srcs/executor/heredoc.c srcs/execution/start.c \
		srcs/execution/tools.c srcs/execution/rederictions.c srcs/execution/ft_split.c srcs/execution/file_errors.c \
		srcs/execution/execute_builtin.c srcs/execution/exec_tools.c srcs/execution/exec_errors.c srcs/execution/exec_commands.c srcs/execution/child_routine.c \
		srcs/execution/builtins/builtin_echo.c srcs/execution/builtins/builtin_env.c srcs/execution/builtins/builtin_exit.c srcs/execution/builtins/builtin_pwd.c srcs/env/ft_getenv.c \
		srcs/env/realloc_env.c srcs/env/is_valid_env_key.c srcs/env/init_env.c srcs/env/ft_unsetenv.c srcs/env/ft_putenv.c srcs/builtins/builtin_export.c \
		srcs/builtins/builtin_unset.c srcs/execution/builtins/builtin_cd.c


OBJ = $(SRC:%.c=%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJ) -lreadline -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(EXEC)

re: fclean all

.SECONDARY: $(OBJ)

.PHONY: all clean fclean re
