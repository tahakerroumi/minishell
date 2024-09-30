NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror
CC			= cc

SRCS		= $(wildcard srcs/*.c srcs/*/*.c)
OBJS		= $(SRCS:.c=.o)

INCLUDES	= includes/

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDES) -o $(NAME) $(OBJS) -lreadline

$(OBJS) : $(INCLUDES)/minishell.h

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all re clean fclean
.SECONDARY: $(OBJS)
