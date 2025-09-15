#include "../cub3d.h"

void init_types(t_data *data)
{
	data->key.W = 0;
	data->key.S = 0;
	data->key.A = 0;
	data->key.D = 0;
	data->key.Es = 0;
	data->key.arrow_left = 0;
	data->key.arrow_up = 0;
	data->key.arrow_down = 0;
	data->key.arrow_right = 0;
}

void mov_player(t_data *data)
{
	double	mov_speed = 0.005;
	double rotSpeed = 0.003;
	double oldDirX = 0.0;
	double oldPlanX = 0.0;
	double	new_y = 0.5;
	double	new_x = 0.5;

	if (data->key.W)
	{
		new_y = data->player.pos.y + data->player.dir.y * mov_speed;
		if (data->map.map[(int)(new_y)][(int)data->player.pos.x] != '1')
			data->player.pos.y = new_y;
		new_x = data->player.pos.x + data->player.dir.x * mov_speed;
		if (data->map.map[(int)(data->player.pos.y)][(int)new_x] != '1')
			data->player.pos.x = new_x;
	}
	if (data->key.S)
	{
		new_y = data->player.pos.y - data->player.dir.y * mov_speed;
		if (data->map.map[(int)(new_y)][(int)data->player.pos.x] != '1')
			data->player.pos.y = new_y;
		new_x = data->player.pos.x - data->player.dir.x * mov_speed;
		if (data->map.map[(int)(data->player.pos.y)][(int)new_x] != '1')
			data->player.pos.x = new_x;
	}
	if (data->key.A)
	{
		new_y = data->player.pos.y - data->player.camera_plane.y * mov_speed;
		if (data->map.map[(int)(new_y)][(int)data->player.pos.x] != '1')
			data->player.pos.y = new_y;
		new_x = data->player.pos.x - data->player.camera_plane.x * mov_speed;
		if (data->map.map[(int)data->player.pos.y][(int)new_x] != '1')
			data->player.pos.x = new_x;
	}
	if (data->key.D)
	{
		new_y = data->player.pos.y + data->player.camera_plane.y * mov_speed;
		if (data->map.map[(int)new_y][(int)data->player.pos.x] != '1')
			data->player.pos.y = new_y;
		new_x = data->player.pos.x + data->player.camera_plane.x * mov_speed;
		if (data->map.map[(int)data->player.pos.y][(int)new_x] != '1')
			data->player.pos.x = new_x;
	}
	if (data->key.arrow_left)
	{
		oldDirX = data->player.dir.x;
        data->player.dir.x = data->player.dir.x * cos(-rotSpeed) - data->player.dir.y * sin(-rotSpeed);
        data->player.dir.y = oldDirX * sin(-rotSpeed) + data->player.dir.y * cos(-rotSpeed);

        oldPlanX = data->player.camera_plane.x;
        data->player.camera_plane.x = data->player.camera_plane.x * cos(-rotSpeed) - data->player.camera_plane.y * sin(-rotSpeed);
        data->player.camera_plane.y = oldPlanX * sin(-rotSpeed) + data->player.camera_plane.y * cos(-rotSpeed);
	}
	if (data->key.arrow_right)
	{
		oldDirX = data->player.dir.x;
        data->player.dir.x = data->player.dir.x * cos(rotSpeed) - data->player.dir.y * sin(rotSpeed);
        data->player.dir.y = oldDirX * sin(rotSpeed) + data->player.dir.y * cos(rotSpeed);

        oldPlanX = data->player.camera_plane.x;
        data->player.camera_plane.x = data->player.camera_plane.x * cos(rotSpeed) - data->player.camera_plane.y * sin(rotSpeed);
        data->player.camera_plane.y = oldPlanX * sin(rotSpeed) + data->player.camera_plane.y * cos(rotSpeed);
	}
}

int key_press(int code, t_data *data)
{
	if (code == 97)
		data->key.A = 1;
	if (code == 100)
		data->key.D = 1;
	if (code == 115)
		data->key.S = 1;
	if (code == 119)
		data->key.W = 1;
	if (code == 65307)
	{
		data->key.Es = 1;
		clean_all(data);
	}
	if (code == 65361)
		data->key.arrow_left = 1;
	if (code == 65362)
		data->key.arrow_up = 1;
	if (code == 65363)
		data->key.arrow_right = 1;
	if (code == 65364)
		data->key.arrow_down = 1;
	return (0);
}

int key_press_release(int code, t_data *data)
{
	if (code == 97)
		data->key.A = 0;
	if (code == 100)
		data->key.D = 0;
	if (code == 115)
		data->key.S = 0;
	if (code == 119)
		data->key.W = 0;
	if (code == 65307)
		data->key.Es = 0;
	if (code == 65361)
		data->key.arrow_left = 0;
	if (code == 65362)
		data->key.arrow_up = 0;
	if (code == 65363)
		data->key.arrow_right = 0;
	if (code == 65364)
		data->key.arrow_down = 0;
	return (0);
}