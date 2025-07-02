#include "../cub3d.h"

void	my_engine(t_data *data)
{
	int x;

	x = 0;
	while (x < WIDTH)
	{
		float	cameraX = 2 * x / (float)WIDTH - 1;
		float rayDirX = data->player.dir.x + data->player.camera_plane.x * cameraX;
		float rayDirY = data->player.dir.y + data->player.camera_plane.y * cameraX;

		int	mapX = (int)data->player.pos.x;
		int	mapY = (int)data->player.pos.y;

		float	sideDistX;
		float	sideDistY;

		float	deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		float	deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		int	stepX;
		int	stepY;
		int	hit = 0;
		int	side;
		float	perpWallDist;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->player.pos.x - mapX) * deltaDistX; 
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->player.pos.x) * deltaDistX; 
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->player.pos.y - mapY) * deltaDistY; 
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player.pos.y) * deltaDistY; 
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map.map[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		int	lineHeight = (int)(HEIGHT / perpWallDist);
		int	start = -lineHeight / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int end = lineHeight / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
		for (int i = 0; i <= start; i++)
		{
			my_mlx_put_pixel(&data->img, i, x, 0x008eecf5);
		}
		for (int i = end; i < HEIGHT - 1; i++)
		{
			my_mlx_put_pixel(&data->img, i, x, 0x009a8c98);
		}
		drawVerLine(&data->img, x, start, end);
		x++;
	}
}


//NÃO MECHE AQUI
/*
// data->r3d.mult = 2 * (x / (float)WIDTH) - 1;
		// data->r3d.camaraPixel = mult_vector(data->player.camera_plane,
		// data->r3d.mult);
		// data->r3d.rayDir = sum_vector(data->player.dir, data->r3d.camaraPixel);
		// printf("posY->%.2f\nposX->%.2f\ndirY->%.2f\ndirX->%.2f\n", data->player.pos.y, data->player.pos.x, data->player.dir.y, data->player.dir.x);
		
		// printf("camera_planeY->%.2f\ncamera_planeX->%.2f\n", data->player.camera_plane.y, data->player.camera_plane.x);
		// printf("camaraPixelY->%.2f\ncamaraPixelX->%.2f\n", data->r3d.camaraPixel.x, data->r3d.camaraPixel.x);
		//calcuted rayasting



		if (data->r3d.rayDir.x == 0)
			data->r3d.deltaDist.x = 1e30;
		else
			data->r3d.deltaDist.x = fabs(1 / data->r3d.rayDir.x);
		if (data->r3d.rayDir.y == 0)
			data->r3d.deltaDist.y = 1e30;
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
		float	perpWallDist;
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
			if (data->map.map[data->r3d.mapPos.y][data->r3d.mapPos.x] != '0')
				hit = 1;
		}
		int	lineHeight;
		if (side == 0)
		{
			perpWallDist = (data->r3d.sideDist.x - data->r3d.deltaDist.x);
		}
		else
		{
			perpWallDist = (data->r3d.sideDist.y - data->r3d.deltaDist.y);
		}
		
		lineHeight = (int)(HEIGHT /perpWallDist);
		int	start = -lineHeight / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int	end = lineHeight / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;

		for (int i = 0; i <= start; i++)
		{
			my_mlx_put_pixel(&data->img, i, x, 0x008eecf5);
		}
		for (int i = end; i < HEIGHT - 1; i++)
		{
			my_mlx_put_pixel(&data->img, i, x, 0x009a8c98);
		}
		
		
		drawVerLine(&data->img, x, start, end);
		x++;
*/