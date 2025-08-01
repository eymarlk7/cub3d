#ifndef CUB3D_H
# define CUB3D_H

/* ----------------------------- DEFINES ----------------------------- */
# define WALL 64
# define TEX_SIZE 64

# define WIDTH 600
# define HEIGHT 400
# define BUFFER_SIZE 42

/* ----------------------------- INCLUDES ----------------------------- */
# include "colors.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"

/* ----------------------------- COLORS ----------------------------- */
# define FLOOR     0x009a8c98
# define SKY       0x008eecf5
# define RED       0xFF0000
# define BLUE      0x0000ff
# define GREEN     0x008000
# define WHITE     0xffffff
# define DARKRED   0x8b0000

/* ----------------------------- ERROR MESSAGES ----------------------------- */
# define ERR_FILE_NOT_CUB     "Not a .cub file"
# define ERR_FILE_NOT_XPM     "Not an .xpm file"
# define ERR_FILE_IS_DIR      "Is a directory"
# define ERR_FLOOR_CEILING    "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR      "Invalid floor RGB color"
# define ERR_COLOR_CEILING    "Invalid ceiling RGB color"
# define ERR_INVALID_MAP      "Map description is either wrong or incomplete"
# define ERR_INV_LETTER       "Invalid character in map"
# define ERR_NUM_PLAYER       "Map has more than one player"
# define ERR_TEX_RGB_VAL      "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING      "Missing texture(s)"
# define ERR_TEX_INVALID      "Invalid texture(s)"
# define ERR_COLOR_MISSING    "Missing color(s)"
# define ERR_MAP_MISSING      "Missing map"
# define ERR_MAP_TOO_SMALL    "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS     "Map is not surrounded by walls"
# define ERR_MAP_LAST         "Map is not the last element in file"
# define ERR_PLAYER_POS       "Invalid player position"
# define ERR_PLAYER_DIR       "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC           "Could not allocate memory"
# define ERR_MLX_START        "Could not start mlx"
# define ERR_MLX_WIN          "Could not create mlx window"
# define ERR_MLX_IMG          "Could not create mlx image"

/* ----------------------------- ENUMS ----------------------------- */
enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR     = 2,
	BREAK   = 3,
	CONTINUE = 4
};

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST  = 2,
	WEST  = 3
};

/* ----------------------------- STRUCTS ----------------------------- */
typedef struct s_point
{
	int	y;
	int	x;
}	t_point;

typedef struct s_vec
{
	float	y;
	float	x;
}	t_vec;

typedef struct s_keypress
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	es;
}	t_key;

typedef struct s_img
{
	int		bpp;
	char	*addr;
	int		endian;
	int		line_lenght;
	void	*img_ptr;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_win;
	void	*mlx_ptr;
}	t_mlx;

typedef struct s_map
{
	int		fd;
	int		line_count;
	char	*path;
	char	**file;
	int		height;
	int		width;
	int		index_end_of_map;
	char	**map;
}	t_map;

typedef struct s_player
{
	t_vec	dir;
	t_vec	pos;
	t_vec	camera_plane;
}	t_player;

typedef struct s_cast
{
	float		mult;
	int			side;
	int			stepX;
	int			stepY;
	t_point		mapPos;
	t_vec		rayDir;
	t_vec		sideDist;
	t_vec		deltaDist;
	t_vec		camaraPixel;
	float		perpWallDist;
}	t_cast;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_data
{
	t_mlx		mlx;
	t_img		img;
	t_map		map;
	t_point		point;
	t_key		key;
	t_player	player;
	t_cast		r3d;
	t_texinfo	texinfo;
}	t_data;

/* ----------------------------- FUNCTION PROTOTYPES ----------------------------- */
// Init
void	init_types(t_data *data);
void	init_mlx(t_mlx *mlx);
void	init_img(t_img *img);
void	init_data(t_data *data, char *argv);
void	init_map_info(t_map *map);
void	init_texinfo(t_texinfo *textures);

// Map / File
int		init_map(t_data *map, char *argv);
int		open_file(char *arg);
char	**get_map(int fd);
int		get_file_data(t_data *data, char **map);
int		create_map(t_data *data, char **file, int i);
size_t	find_biggest_len(t_map *map, int i);

// Player
int		get_player_dir(t_player *player, char **map);
int		get_player_pos(t_player *player, char **map);
void	mov_player(t_data *data);

// Engine
void	my_engine(t_data *data);

// Drawing
void	drawVerLine(t_img *img, int x, t_point new_points, int color);
void	my_mlx_put_pixel(t_img *img, int y, int x, int color);

// Events
int		key_press(int code, t_data *data);
int		key_press_release(int code, t_data *data);

// Utils
void	clean_all(t_data *data);
int		err_msg(char *detail, char *str, int code);
int		err_msg_val(int detail, char *str, int code);
int		fill_color_textures(t_data *data, t_texinfo *textures, char *line, int j);
void	free_tab(void **tab);
void	debug_print_char_tab(char **tab);
void	debug_display_mapinfo(t_data *data);

// Vector
t_vec	create_vector(float y, float x);
t_vec	sum_vector(t_vec v1, t_vec v2);
t_vec	mult_vector(t_vec vector, float num);

#endif /* CUB3D_H */
