CC = cc

CFLAGS = -Wall -Wextra -Werror

EXEC = minishell

LIBFT = libft/libft.a

SRC = main.c env.c

OBJ = $(SRC:%.c=%.o)

all: $(EXEC)

$(EXEC): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		make -C libft/

clean:
	rm -rf $(OBJ)
	make clean -C libft/

fclean: clean
	rm -rf $(EXEC)
	make fclean -C libft/

re: fclean all

.SECONDARY: $(OBJ)

.PHONY: all clean fclean re