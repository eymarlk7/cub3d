#include "../cub3d.h"

void	my_engine(t_data *data)
{
	int x;

	x = 0;
	while (x < WIDTH)
	{
		data->r3d.mult = 2 * (x / (float)WIDTH) - 1;
		data->r3d.camaraPixel = mult_vector(data->player.camera_plane,
		data->r3d.mult);
		data->r3d.rayDir = sum_vector(data->player.dir, data->r3d.camaraPixel);

		//calcuted rayasting
		if (data->r3d.rayDir.x == 0)
			data->r3d.deltaDist.x = 1e30;
		else
			data->r3d.deltaDist.x = fabs(1 / data->r3d.rayDir.x);
		if (data->r3d.rayDir.y == 0)
			data->r3d.deltaDist.x = 1e30;
		else
			data->r3d.deltaDist.y = fabs(1 / data->r3d.rayDir.y);
		
		data->r3d.mapPos = (t_point){(int)data->player.pos.y, (int)data->player.pos.x};
		int stepX;
		int stepY;
		if (data->r3d.rayDir.x < 0)
		{
			stepX = -1;
			data->r3d.sideDist.x = (data->player.pos.x - data->r3d.mapPos.x) * data->r3d.deltaDist.x;
		}
		else
		{
			stepX = 1;
			data->r3d.sideDist.x = (data->r3d.mapPos.x + 1.00 - data->player.pos.x) * data->r3d.deltaDist.x;
		}
		if (data->r3d.rayDir.y < 0)
		{
			stepY = -1;
			data->r3d.sideDist.y = (data->player.pos.y - data->r3d.mapPos.y) * data->r3d.deltaDist.y;
		}
		else
		{
			stepY = 1;
			data->r3d.sideDist.y = (data->r3d.mapPos.y + 1.00 - data->player.pos.y) * data->r3d.deltaDist.y;
		}

		int	hit = 0;
		int	side;
		double	perpWallDist;
		while (hit == 0)
		{
			if (data->r3d.sideDist.x < data->r3d.sideDist.y)
			{
				data->r3d.sideDist.x += data->r3d.deltaDist.x;
				data->r3d.mapPos.x += stepX;
				side = 0;
			}
			else
			{

				data->r3d.sideDist.y += data->r3d.deltaDist.y;
				data->r3d.mapPos.y += stepY;
				side = 1;
			}
			if (data->map.map[data->r3d.mapPos.y][data->r3d.mapPos.x] > 0)
				hit = 1;
		}
		int	lineHeight;
		if (side == 0)
		{
			perpWallDist = (data->r3d.sideDist.x - data->r3d.deltaDist.x);
			lineHeight = (int)(HEIGHT /perpWallDist);

		}
		else
		{
			perpWallDist = (data->r3d.sideDist.y - data->r3d.deltaDist.y);
			lineHeight = (int)(HEIGHT /perpWallDist);
			printf("start->%d\n", (int)(HEIGHT / perpWallDist));
		}
		int	start = lineHeight / 2 - HEIGHT / 2;
		if (start < 0)
			start = 0;
		int	end = lineHeight / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
		
		drawVerLine(&data->img, x, start, end);
		x++;
	}
}