# Standard
NAME	=	libft.a

# Directories
INC		=	inc/
SRC_DIR	=	src
OBJ_DIR	=	obj

# Compiler & flags
WFLAGS	=	-Wall -Wextra -Werror
IFLAGS	=	-I$(INC)
CC		=	gcc
RM		=	rm -rf
AR		=	ar rcs

# Sources
SRC		=	$(shell find $(SRC_DIR) -type f -name "*.c")

# Objects
OBJ		=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Colors
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
RESET	=	\033[0m

# Build Rules
all:	$(NAME)
	@echo "$(GREEN)Successfully compiled libft!$(RESET)"

$(NAME):	$(OBJ)
	@echo "\n"
	@echo "$(BLUE)Creating$(RESET)\t$(NAME)"
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)Successfully created libft archive!$(RESET)"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@printf "$(YELLOW)Compiling\t$(RESET)%-33.33s\r" $@
	@$(CC) $(WFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Deleting$(RESET)\tlibft $(OBJ_DIR)"
	@$(RM) -r $(OBJ_DIR)

fclean:	clean
	@echo "$(RED)Deleting$(RESET)\t$(NAME)"
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
