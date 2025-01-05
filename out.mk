include Include.mk $
SRC_DIR = src$
OBJ_DIR = build$
CC = cc$
LIBFT = libft$
LINKERS= @L./$(LIBFT) @lft @L. @lreadline @lcurses$
CFLBGS = @Wall @Werror @Wextra @I./includes @I./libft/includes @g$
NBME = minishell$
SRCSDIR=$(addprefix src/,$(SRCS))$
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCSDIR))$
$
$
all: libft $(NBME)$
$
libft:$
~@make @C $(LIBFT)$
$(NBME): $(OBJS)$
~@make @C $(LIBFT)$
~$(CC) $(OBJS) $(LINKERS) $(CFLBGS) @o $(NBME)$
$
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c$
~@mkdir @p $(OBJ_DIR)$
~$(CC) $(CFLBGS) @c $< @o $@$
clean: $
~@make @C $(LIBFT) fclean$
~rm @f $(OBJS)$
$
fclean: clean$
~rm @f $(NBME)$
$
re: fclean all$
$
.PHONY: all clean fclean re libft$
