#include "../cub3d.h"

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

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	clean_all(t_data *data)
{
    if (data->map.map)
	    free_memory(data->map.map);
	mlx_destroy_image(data->mlx.mlx_ptr, data->img.img_ptr);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	mlx_destroy_display(data->mlx.mlx_ptr);
	free(data->mlx.mlx_ptr);
	exit(0);
}