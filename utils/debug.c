#include "../cub3d.h"

void	debug_print_char_tab(char **tab)
{
	int	i;

	printf("\n");
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n");
}

void	debug_display_mapinfo(t_data *data)
{
	// printf(YELLOW "\n---- MAP\n" RESET);
	// printf("Map height: %d\n", data->mapinfo.height);
	// printf("Map width: %d\n", data->mapinfo.width);
	// debug_print_char_tab(data->map);
	printf(BG_BLACK "\n---- TEXTURES & COLORS\n" RESET);
	printf("Color ceiling: #%lx\n", data->texinfo.hex_ceiling);
	printf("Color floor: #%lx\n", data->texinfo.hex_floor);
	printf("Texture north: %s\n", data->texinfo.north);
	printf("Texture south: %s\n", data->texinfo.south);
	printf("Texture east: %s\n", data->texinfo.east);
	printf("Texture west: %s\n", data->texinfo.west);
}