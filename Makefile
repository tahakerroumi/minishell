CC = cc

CFLAGS = -Wall -Wextra -Werror -g

EXEC = minishell

SRC = srcs/main.c srcs/split_int_ptr.c srcs/executor.c srcs/tools.c srcs/ft_split.c srcs/lib_v2.c

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
