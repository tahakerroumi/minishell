CC = cc

CFLAGS = -Wall -Wextra -Werror  -g

EXEC = minishell

INCLUDES = includes/

SRC = 	srcs/main.c srcs/split_int_ptr.c srcs/execution/ft_split.c srcs/execution/start.c srcs/execution/tools.c \
		srcs/execution/exec_tools.c srcs/execution/builtins/pwd.c srcs/execution/file_errors.c srcs/execution/builtins/exit.c \
		srcs/execution/rederictions.c srcs/execution/exec_errors.c srcs/execution/builtins/env.c srcs/execution/builtins/echo.c \
		srcs/execution/exec_commands.c srcs/execution/child_routine.c srcs/execution/execute_builtin.c srcs/execution/ft_strtrim.c \

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
