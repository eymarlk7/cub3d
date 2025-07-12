NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	./src/main.c \
		./src/player.c \
		./src/vector.c \
		./src/init_game.c \
		./src/my_engine.c \
		./src/parsed_map.c \
		./src/player_mov.c \
		./src/draw/draw.c \
		./src/clean_memory.c \
		./init/init_data.c	\
		./utils/debug.c	\
		./src/error.c \
		./src/fill_color_textures.c
OBJ = $(SRCS:.c=.o)
MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -lm 
MLX = ./minilibx-linux/libmlx.a
L_DIR = ./libft
LIBFT = $(L_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -L./minilibx-linux $(MLX_FLAGS) -o $(NAME) $(LIBFT)
	rm -f $(OBJ)

$(MLX):
	$(MAKE) -C ./minilibx-linux

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	rm -f $(OBJ)
	@$(MAKE) clean -C ./minilibx-linux
	@$(MAKE) clean -C ./libft

fclean: clean
	rm -f $(NAME)
	@$(MAKE) clean -C ./minilibx-linux
	@$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re