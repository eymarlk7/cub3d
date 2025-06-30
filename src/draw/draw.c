#include "../../cub3d.h"

void    my_mlx_put_pixel(t_img *img, int y, int x, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_lenght + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	drawVerLine(t_img *img, int x, int start, int end)
{
	int	y;

	y = start;
	while (y <= end)
	{
		my_mlx_put_pixel(img, y, x, 0x00FF0000);
		y++;
	}
}