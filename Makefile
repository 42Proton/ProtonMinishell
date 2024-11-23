SRCS = main.c inbuilt_cmds.c inbuilt_cmds_utils.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft/includes -I.
LIBFT = libft

all: $(NAME)
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L./$(LIBFT) -lft -lreadline -o $(NAME)
$(LIBFT):
	make -C $(LIBFT)
clean:
	rm -f $(OBJS)
	make -C $(LIBFT) clean
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean
re: fclean all
.PHONY: all clean fclean re