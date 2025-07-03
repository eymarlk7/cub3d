#include "../../cub3d.h"

void    my_mlx_put_pixel(t_img *img, int y, int x, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_lenght + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	drawVerLine(t_img *img, int x, t_point new_points, int color)
{
	int	y;

	y = new_points.x;
	while (y <= new_points.y)
	{
		my_mlx_put_pixel(img, y, x, color);
		y++;
	}
}