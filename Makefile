NAME = cub3d

SRCS = 	src/main.c \
		src/close_game.c \
		src/errors.c \
		src/parsing/parsing.c \
		src/parsing/file_checker.c \
		src/parsing/file_checker_utils.c \
		src/parsing/map_checker.c \
		src/parsing/map_checker_utils.c \
		src/parsing/textures_checker.c \
		src/ft_free.c \
		src/init/init.c \
		src/moves/keys_manager.c \
		src/moves/rotate.c \
		src/moves/moves.c \
		src/mlx_pixels/ft_display.c \
		src/mlx_pixels/raycasting.c

OBJS 	= $(SRCS:.c=.o)

RM		= rm -rf

CC 		= cc

CFLAGS 	= -Wall -Wextra -Werror -O3 -flto -march=native -ffast-math

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -Lmlx

%.o : %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

all: 		$(NAME)

$(NAME):	$(OBJS)
	make -C ./libft
	make -C ./mlx
	$(CC) $(OBJS) $(MLXFLAGS) -Llibft -lft -o $(NAME)

clean:
	make clean -C ./libft
	make clean -C ./mlx
	$(RM) $(OBJS)

fclean: 	clean
	make fclean -C ./libft
	$(RM) $(NAME)

re:			fclean all

.PHONY:	all clean fclean re