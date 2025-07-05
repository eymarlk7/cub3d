#include "../cub3d.h"

void init_types(t_data *data)
{
	data->key.es = 0;
	data->key.up = 0;
	data->key.down = 0;
	data->key.left = 0;
	data->key.right = 0;
}

void mov_player(t_data *data)
{
	double	mov_speed = 0.08;
	double rotSpeed = 0.06;
	double oldDirX;
	double oldPlanX;
	double	new_y;
	double	new_x;

	if (data->key.up)
	{
		new_y = data->player.pos.y + data->player.dir.y * mov_speed;
		if (data->map.map[(int)(new_y)][(int)data->player.pos.x] != '1')
			data->player.pos.y = new_y;
		new_x = data->player.pos.x + data->player.dir.x * mov_speed;
		if (data->map.map[(int)(data->player.pos.y)][(int)new_x] != '1')
			data->player.pos.x = new_x;
	}
	if (data->key.down)
	{
		new_y = data->player.pos.y - data->player.dir.y * mov_speed;
		if (data->map.map[(int)(new_y)][(int)data->player.pos.x] != '1')
			data->player.pos.y = new_y;
		new_x = data->player.pos.x - data->player.dir.x * mov_speed;
		if (data->map.map[(int)(data->player.pos.y)][(int)new_x] != '1')
			data->player.pos.x = new_x;
	}
	if (data->key.left)
	{
		oldDirX = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(-rotSpeed) - data->player.dir.y * sin(-rotSpeed);
		data->player.dir.y = oldDirX * sin(-rotSpeed) + data->player.dir.y * cos(-rotSpeed);
		oldPlanX = data->player.camera_plane.x;
		data->player.camera_plane.x = data->player.camera_plane.x * cos(-rotSpeed) - data->player.camera_plane.y * sin(-rotSpeed);
		data->player.camera_plane.y = oldPlanX * sin(-rotSpeed) + data->player.camera_plane.y * cos(-rotSpeed);
	}
	if (data->key.right)
	{
		oldDirX = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(rotSpeed) - data->player.dir.y * sin(rotSpeed);
		data->player.dir.y = oldDirX * sin(rotSpeed) + data->player.dir.y * cos(rotSpeed);
		oldPlanX = data->player.camera_plane.x;
		data->player.camera_plane.x = data->player.camera_plane.x * cos(rotSpeed) - data->player.camera_plane.y * sin(rotSpeed);
		data->player.camera_plane.y = oldPlanX * sin(rotSpeed) + data->player.camera_plane.y * cos(rotSpeed);
	}
}

void	free_memory(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	clean_all(t_data *data)
{
	free_memory(data->map.map);
	mlx_destroy_image(data->mlx.mlx_ptr, data->img.img_ptr);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	mlx_destroy_display(data->mlx.mlx_ptr);
	free(data->mlx.mlx_ptr);
	exit(0);
}

int key_press(int code, t_data *data)
{
	if (code == 119)
		data->key.up = 1;
	if (code == 115)
		data->key.down = 1;
	if (code == 97)
		data->key.left = 1;
	if (code == 100)
		data->key.right = 1;
	if (code == 65307)
	{
		data->key.es = 1;
		clean_all(data);
	}
	return (0);
}

int key_press_release(int code, t_data *data)
{
	if (code == 119)
		data->key.up = 0;
	if (code == 115)
		data->key.down = 0;
	if (code == 97)
		data->key.left = 0;
	if (code == 100)
		data->key.right = 0;
	if (code == 65307)
		data->key.es = 0;
	return (0);
}