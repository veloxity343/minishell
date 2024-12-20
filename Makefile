# Standard
NAME		=	minishell

# Directories
LIBFT		=	./libft/libft.a
INC			=	inc/
SRC_DIR		=	src
OBJ_DIR		=	obj
SRCB_DIR	=	srcb
OBJB_DIR	=	objb

# Compiler & flags
WFLAGS		=	-Wall -Wextra -Werror
IFLAGS		=	-I$(INC) -I/opt/homebrew/Cellar/readline/8.2.13/include
DSYM		=	-g3
FSAN		=	-fsanitize=address $(DSYM)
CFLAGS		=	$(WFLAGS) $(IFLAGS) -D_DARWIN_C_SOURCE
CC			=	cc
RM			=	rm -rf
READLINE	=	-L/opt/homebrew/Cellar/readline/8.2.13/lib -lreadline -lncurses -lhistory

# Sources
SRC			=	$(shell find $(SRC_DIR) -type f -name "*.c")
SRCB		=	$(shell find $(SRCB_DIR) -type f -name "*.c")

# Objects
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJB		=	$(patsubst $(SRCB_DIR)%.c, $(OBJB_DIR)%.o, $(SRCB))

# Colors
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
RESET	=	\033[0m

# Build rules
all:		$(LIBFT) $(NAME)
	@echo "$(GREEN)Successfully compiled minishell!$(RESET)"

$(LIBFT):
	@echo "$(BLUE)Building$(RESET)\tlibft"
	@make -C $(dir $(LIBFT))

$(NAME):	$(OBJ)
	@echo "\n"
	@echo "$(BLUE)Building$(RESET)\t$(NAME)"
	@make -s -C $(dir $(LIBFT))
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(READLINE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling\t$(RESET)%-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

bonus:		clean $(OBJ) $(OBJB)
	@echo "$(BLUE)Linking bonus objects...$(RESET)"
	@make -C $(dir $(LIBFT))
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJB) $(LIBFT) $(READLINE)
	@echo "$(GREEN)Successfully compiled bonus!$(RESET)"

$(OBJB_DIR)/%.o: $(SRCB_DIR)/%.c | $(OBJB_DIR)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling$(RESET)\t$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJB_DIR):
	@mkdir -p $(OBJB_DIR)

clean:
	@echo "$(RED)Deleting$(RESET)\t$(OBJ_DIR)"
	@$(RM) -rf $(OBJ_DIR)
	@if [ -d $(OBJB_DIR) ]; then \
		echo "$(RED)Deleting$(RESET)\t$(OBJB_DIR)"; \
		$(RM) -rf $(OBJB_DIR); \
	fi

fclean:	clean
	@echo "$(RED)Deleting$(RESET)\t$(NAME)"
	@$(RM) -f $(NAME)
	@make fclean -C $(dir $(LIBFT))

re:		fclean all

debug:	CFLAGS	+=	$(FSAN)
debug:	fclean test

test:	$(NAME)
	@echo "$(BLUE)Testing with debugging on$(RESET)"
	@echo "$(YELLOW)Running minishell...$(RESET)"
	./$(NAME)

norm:
	norminette

.PHONY:	all bonus clean fclean re debug test norm
