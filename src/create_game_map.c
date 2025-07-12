#include "../cub3d.h"


static int	count_map_lines(t_data *data, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	data->map.index_end_of_map = i;
	return (i - index_value);
}

static int	fill_map_tab(t_map *map, char **map_tab, int index)
{
	int		i;
	int		j;

	map->width = find_biggest_len(map, index);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		map_tab[i] = malloc(sizeof(char) * (map->width + 1));
		if (!map_tab[i])
			return (err_msg(NULL, ERR_MALLOC, FAILURE));
		while (map->file[index][j] && map->file[index][j] != '\n')
		{
			map_tab[i][j] = map->file[index][j];
			j++;
		}	
		while (j < map->width)
			map_tab[i][j++] = '\0';
		i++;
		index++;
	}
	map_tab[i] = NULL;
	return (SUCCESS);
}

static int	get_map_info(t_data *data, char **file, int i)
{
	data->map.height = count_map_lines(data, file, i);
	data->map.map = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.map)
		return (err_msg(NULL, ERR_MALLOC, FAILURE));
	if (fill_map_tab(&data->map, data->map.map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	change_space_into_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j] == ' ' || data->map.map[i][j] == '\t'
		|| data->map.map[i][j] == '\r'
		|| data->map.map[i][j] == '\v' || data->map.map[i][j] == '\f')
			j++;
		while (data->map.map[i][++j])
		{
			if (data->map.map[i][j] == ' '
				&& j != data->map.map[i][ft_strlen(data->map.map[i]) - 1])
				data->map.map[i][j] = '1';
		}
		i++;
	}
}


int	create_map(t_data *data, char **file, int i)
{
	if (get_map_info(data, file, i) == FAILURE)
		return (FAILURE);
	change_space_into_wall(data);
	return (SUCCESS);
}