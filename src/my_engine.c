#include "../cub3d.h"

void	get_someVals(t_data *data)
{
	data->r3d.mapPos = (t_point)
	{
		(int)data->player.pos.y,
		(int)data->player.pos.x
	};
	data->r3d.deltaDist.x = (data->r3d.rayDir.x == 0)
	? 1e30 : fabs(1 / data->r3d.rayDir.x);
	data->r3d.deltaDist.y = (data->r3d.rayDir.y == 0)
	? 1e30 : fabs(1 / data->r3d.rayDir.y);
}

void	set_sideDistVal(t_data *data)
{
	if (data->r3d.rayDir.x < 0)
	{
		data->r3d.stepX = -1;
		data->r3d.sideDist.x = (data->player.pos.x - data->r3d.mapPos.x)
		* data->r3d.deltaDist.x; 
	}
	else
	{
		data->r3d.stepX = 1;
		data->r3d.sideDist.x = (data->r3d.mapPos.x + 1.0 - data->player.pos.x)
		* data->r3d.deltaDist.x; 
	}
	if (data->r3d.rayDir.y < 0)
	{
		data->r3d.stepY = -1;
		data->r3d.sideDist.y = (data->player.pos.y - data->r3d.mapPos.y)
		* data->r3d.deltaDist.y; 
	}
	else
	{
		data->r3d.stepY = 1;
		data->r3d.sideDist.y = (data->r3d.mapPos.y + 1.0 - data->player.pos.y)
		* data->r3d.deltaDist.y; 
	}
}

void	dda(t_data *data)
{
	while (data->map.map[data->r3d.mapPos.y][data->r3d.mapPos.x])
	{
		if (data->r3d.sideDist.x < data->r3d.sideDist.y)
		{
			data->r3d.sideDist.x += data->r3d.deltaDist.x;
			data->r3d.mapPos.x += data->r3d.stepX;
			data->r3d.side = 0;
		}
		else
		{
			data->r3d.sideDist.y += data->r3d.deltaDist.y;
			data->r3d.mapPos.y += data->r3d.stepY;
			data->r3d.side = 1;
		}
		if (data->map.map[data->r3d.mapPos.y][data->r3d.mapPos.x] == '1')
			break;
	}
}

void	draw_on_screen(t_data *data, int x, int color)
{
	int	i;
	int	j;
	t_point	new_points;
	int	lineHeight;
	
	i = 0;
	lineHeight = (int)(HEIGHT / data->r3d.perpWallDist);
	new_points.x = -lineHeight / 2 + HEIGHT / 2;
	if (new_points.x < 0)
		new_points.x = 0;
	new_points.y = lineHeight / 2 + HEIGHT / 2;
	if (new_points.y >= HEIGHT)
		new_points.y = HEIGHT - 1;
	while (i <= new_points.x)
		my_mlx_put_pixel(&data->img, i++, x, SKY);
	j = new_points.y;
	while (j < HEIGHT - 1)
		my_mlx_put_pixel(&data->img, j++, x, FLOOR);
	drawVerLine(&data->img, x, new_points, color);
}

void	my_engine(t_data *data)
{	
	int x;
	int	color;

	x = 0;
	while (x < WIDTH)
	{
		color = RED;
		data->r3d.mult = 2 * x / (float)WIDTH - 1;
		data->r3d.camaraPixel = mult_vector(data->player.camera_plane, data->r3d.mult);
		data->r3d.rayDir = sum_vector(data->player.dir, data->r3d.camaraPixel);
		get_someVals(data);
		set_sideDistVal(data);
		dda(data);
		if (data->r3d.side == 0)
		{
			data->r3d.perpWallDist = (data->r3d.sideDist.x - data->r3d.deltaDist.x);
			color = DARKRED;
		}
		else
			data->r3d.perpWallDist = (data->r3d.sideDist.y - data->r3d.deltaDist.y);
		draw_on_screen(data, x, color);
		x++;
	}
}

