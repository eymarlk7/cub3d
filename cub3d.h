#ifndef CUB3D_H

# define CUB3D_H
# define WALL 64
# define WIDTH 600
# define HEIGHT 400
# define BUFFER_SIZE 42

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"

typedef struct map
{
	char	**map;
}	t_map;

typedef	struct s_point
{
	int	y;
	int	x;
}	t_point;

typedef struct s_img
{
	int		bpp;
	char		*addr;
	int		endian;
	int		line_lenght;
	void		*img_ptr;
}	t_img;

typedef struct s_vector
{
	float	y;
	float	x;
}	t_vec;

typedef struct s_mlx
{
	void	*mlx_win;
	void	*mlx_ptr;
}	t_mlx;

typedef struct s_player
{
	t_vec	dir;
	t_vec	pos;
	t_vec	camera_plane;
}	t_player;

typedef struct s_engine
{
	t_vec	rayDir;
	t_vec	sideDist;
	t_vec	deltaDist;
	t_vec	camaraPixel;
	t_point	mapPos;
	float	mult;
}	t_cast;

typedef struct s_data
{
	t_mlx	mlx;
	t_img	img;
	t_map	map;
	t_point	point;
	t_player player;
	t_cast	r3d;
}	t_data;


/* FUNCTIONS */
int	init_map(t_map	*map, char *argv);
void	init_mlx(t_mlx *mlx);
void	init_data(t_data *data, char *argv);
void	my_engine(t_data *data);
char	**get_map(int fd);
int		open_file(char *arg);

int     get_player_dir(t_player *player, char **map);
int     get_player_pos(t_player *player, char **map);

void	init_img(t_img *img);
void	drawVerLine(t_img *img, int x, int start, int end);
void    my_mlx_put_pixel(t_img *img, int y, int x, int color);

t_vec	sum_vector(t_vec v1, t_vec v2);
t_vec	create_vector(float y, float x);
t_vec	mult_vector(t_vec vector, float num);

#endif