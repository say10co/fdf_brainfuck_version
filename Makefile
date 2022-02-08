
FILES = parser_f.c

GNL_FILES = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

FLAGS = -Wall -Werror -Wextra

OPEN_GL = -lmlx -framework OpenGL -framework AppKit
D = -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit
NAME = fdf


all: $(NAME)

$(NAME):  LIB
	cc $(FLAGS)  -L./libft -lft $(D) $(FILES) $(GNL_FILES)  -o $@

LIB:
	make -C ./libft
	make bonus -C ./libft

clean:
	make clean -C ./libft
	rm -rf $(NAME)
	
fclean: clean
	make fclean -C ./libft

re: fclean all

