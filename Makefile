SRCS = main.c inbuilt_cmds.c inbuilt_cmds_utils.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft/includes -I.
LIBFT = libft/libft.a

all: $(NAME)
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lreadline -o $(NAME)
$(LIBFT):
	make -C libft
clean:
	rm -f $(OBJS)
	make -C libft clean
fclean: clean
	rm -f $(NAME)
	make -C libft fclean
re: fclean all
.PHONY: all clean fclean re