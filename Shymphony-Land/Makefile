CC = cc

CFLAGS = -Wall -Wextra -Werror -g ##-fsanitize=address

EXEC = minishell

SRC = srcs/main.c srcs/split_int_ptr.c srcs/execution/ft_split.c srcs/execution/start.c srcs/execution/tools.c \
		srcs/execution/exec_tools.c

OBJ = $(SRC:%.c=%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(EXEC)

re: fclean all

.SECONDARY: $(OBJ)

.PHONY: all clean fclean re
