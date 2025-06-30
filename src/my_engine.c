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
		data->r3d.deltaDist.x = fabs(1 / data->r3d.rayDir.x);
		data->r3d.deltaDist.y = fabs(1 / data->r3d.rayDir.y);

		x++;
	}
}