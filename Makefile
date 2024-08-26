# Standard
NAME		=	minishell

# Directories
LIBFT		=	./libft/libft.a
INC			=	inc/
SRC_DIR		=	src/
OBJ_DIR		=	obj/
SRCB_DIR	=	srcb/
OBJB_DIR	=	objb/

# Compiler & flags
WFLAGS		=	-Wall -Wextra -Werror
IFLAGS		=	-I$(INC)
DSYM		=	-g3
FSAN		=	-fsanitize=address $(DSYM)
CFLAGS		=	$(WFLAGS) $(IFLAGS)
CC			=	gcc
RM			=	rm -rf

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
all:		$(NAME)
	@echo "$(GREEN)Successfully compiled!$(RESET)"

$(NAME):	$(OBJ)
	@make -C $(dir $(LIBFT))
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling\t$(RESET)$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

bonus:		clean $(OBJ) $(OBJB)
	@echo "$(BLUE)Linking bonus objects...$(RESET)"
	@make -C $(dir $(LIBFT))
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJB) $(LIBFT)
	@echo "$(GREEN)Successfully compiled bonus!$(RESET)"

$(OBJB_DIR)%.o: $(SRCB_DIR)%.c | $(OBJB_DIR)
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling\t$(RESET)$<"
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
	@make clean -C $(dir $(LIBFT))

fclean:	clean
	@echo "$(RED)Deleting$(RESET)\t$(NAME)"
	@$(RM) -f $(NAME)
	@$(RM) -f $(LIBFT)/libft.a

re:		fclean all

debug:	CFLAGS	+=	$(FSAN)
debug:	test

test:	$(NAME)
	@echo "$(BLUE)Testing with debugging on\n$(RESET)"
	@echo "$(YELLOW)Running minishell...\n$(RESET)"
	./$(NAME)

.PHONY:	all bonus clean fclean re debug test
