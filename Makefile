SRCS = main.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L. -lreadline -o $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re