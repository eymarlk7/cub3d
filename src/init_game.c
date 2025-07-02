#include "../cub3d.h"

void	init_player(t_player *player, char **map)
{
	(void)map;
	player->pos.x = 5.5;
	player->pos.y = 5.5;
	player->dir.x = 0;
	player->dir.y = -1;
	player->camera_plane.x = 0.66;
	player->camera_plane.y = 0;
	//NÃO MECHE AQUI
	// get_player_pos(player, map);
	// get_player_dir(player, map);
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


void	init_game(t_data *data, char *argv)
{
	
	init_mlx(&data->mlx);
	data->img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	init_img(&data->img);
	if (init_map(&data->map, argv) == -1)
		return ;
	init_player(&data->player, data->map.map);
}

void	init_data(t_data *data, char *argv)
{
	init_game(data, argv);
}