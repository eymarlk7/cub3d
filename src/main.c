#include "../cub3d.h"

int	render_frame(t_data *data)
{
	mov_player(data);
	my_engine(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_win, data->img.img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (printf("Too few arguments\n"), 2);
	init_data(&data, argv[1]);
	init_types(&data);
	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.mlx_win, 3, 1L << 1, key_press_release, &data);

	mlx_loop_hook(data.mlx.mlx_ptr, render_frame, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
