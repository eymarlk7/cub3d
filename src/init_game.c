#include "../cub3d.h"

void	init_player(t_player *player, char **map)
{
	(void)map;
	player->pos = (t_vec){0.0, 0.0};
	player->dir = (t_vec){0.0, 0.0};
	player->camera_plane = (t_vec){0.0, 0.0};
	get_player_pos(player, map);
	get_player_dir(player, map);
}

void	init_img(t_img *img)
{
	img->addr = mlx_get_data_addr
	(
		img->img_ptr,
		&img->bpp,
		&img->line_lenght,
		&img->endian
	);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Cub3d game");
}

void	init_engine(t_cast *cast)
{
	cast->side = 0;
	cast->stepX = 0;
	cast->stepY = 0;
	cast->mult = 0.0;
	cast->perpWallDist = 0.0;
	cast->mapPos = (t_point){0, 0};
	cast->rayDir = (t_vec){0.0, 0.0};
	cast->sideDist = (t_vec){0.0, 0.0};
	cast->deltaDist = (t_vec){0.0, 0.0};
	cast->camaraPixel = (t_vec){0.0, 0.0};
}

void	init_game(t_data *data, char *argv)
{
	init_mlx(&data->mlx);
	data->img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	init_img(&data->img);
	if (init_map(&data->map, argv) == -1)
		return ;
	init_player(&data->player, data->map.map);
	init_engine(&data->r3d);
}

void	init_data(t_data *data, char *argv)
{
	init_game(data, argv);
}