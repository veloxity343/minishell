# Standard
NAME	=	libft.a

# Directories
INC		=	inc/
SRC_DIR	=	src/
OBJ_DIR	=	obj/

# Compiler & flags
WFLAGS	=	-Wall -Wextra -Werror
IFLAGS	=	-I$(INC)
CC		=	gcc
RM		=	rm -rf
AR		=	ar rcs

# Sources
SRC		=	$(shell find $(SRC_DIR) -type f -name "*.c")

# Objects
OBJ		=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)/%.o,$(SRC))

# Build Rules
all:	$(NAME)

$(NAME):	$(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(WFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
