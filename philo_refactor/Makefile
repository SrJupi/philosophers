NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD

# Folders
SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep
INC_DIR = inc

# Source files
SRC = main.c check_args.c philo_routine.c time_utils.c state_utils.c forks_utils.c loop_utils.c print_utils.c clean_utils.c init_utils.c

# Object files
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

# Compile SRC files and move to folders
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/philo_r.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -O3 -c $< -o $@ 
	@mkdir -p $(DEP_DIR)
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -fsanitize=thread
	@echo "Philo compiled!"

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)


fclean:
	rm -rf $(NAME) $(OBJ_DIR) $(DEP_DIR)


re:	fclean all

-include $(DEP)

.PHONY: all re clean fclean