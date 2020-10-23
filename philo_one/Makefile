NAME			= philo_one
HEADER			= includes/
SRCS_PATH 		= srcs/
SRCS_NAME		= main.c utils.c libft.c get_time.c display.c status.c life.c
SRCS 			= $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ_PATH		= obj/
OBJ_NAME		= ${SRCS_NAME:.c=.o}
OBJ				= $(addprefix $(OBJ_PATH),$(OBJ_NAME))
FLAGS			= -Wall -Werror -Wextra -g3 -O3 -fsanitize=address
RM				= rm -rf

all: $(OBJ_PATH) $(NAME) $(HEADER)
	@:

$(NAME): $(OBJ) Makefile
	@gcc $(FLAGS) $(OBJ) -o $(NAME) -lpthread
	@printf "\033[2K\r$(DARK_BLUE)$(NAME) : $(LIGHT_GREEN)Updated\n\033[0m"

$(OBJ_PATH):
	@mkdir -p obj/ 2> /dev/null

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(HEADER) Makefile
	@printf "\033[2K\r$(LIGHT_RED)Compiling : \033[37m%-30s\033[36m \033[0m" $<
	gcc $(FLAG) -I $(HEADER) -c $< -o $@

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

norme:
	~/.norminette/norminette.rb $(SRCS)

.PHONY: all clean fclean re

