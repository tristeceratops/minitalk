NAME := client
NAME_S := server
FLAGS := -Wall -Wextra -Werror
FILES := client.c
FILES_S := server.c
OBJ := $(FILES:.c=.o)
OBJ_S := $(FILES_S:.c=.o)
LIBFT := libft/
LIBFT_LIB := libft.a

all: do_libft $(NAME) $(NAME_S)

$(NAME): $(OBJ) $(OBJ_S)
		cc $(FLAGS) $(OBJ) -L$(LIBFT) -lft -o $@

$(NAME_S): $(OBJ) $(OBJ_S)
		cc $(FLAGS) $(OBJ_S) -L$(LIBFT) -lft -o $@

%.o: %.c
		cc $(FLAGS) -c $< -o $@

do_libft:
		make -C $(LIBFT)
		make bonus -C $(LIBFT)

clean:
		make clean -C $(LIBFT)
		rm -f $(OBJ) $(OBJ_S)

fclean: clean
		make fclean -C $(LIBFT)
		rm -f $(NAME) $(NAME_S)

re: fclean all