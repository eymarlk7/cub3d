#include "../cub3d.h"

void init_map_info(t_map *map)
{
 	map->fd = 0;
	map->line_count = 0;
	map->path = NULL;
	map->file = NULL;
	map->height = 0;
	map->width = 0;
	map->index_end_of_map = 0;   
}

void	init_texinfo(t_texinfo *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
	textures->size = TEX_SIZE;
	textures->step = 0.0;
	textures->pos = 0.0;
	textures->x = 0;
	textures->y = 0;
}


static char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	fill_direction_textures(t_texinfo *textures, char *line, int j)
{
	// if (line[j + 2] && ft_isprint(line[j + 2]))
	// {
	// printf("XXXXXXXXXXXXXX", );

	// 	return (ERR);

	// }
	if (line[j] == 'N' && line[j + 1] == 'O' && !(textures->north))
		textures->north = get_texture_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(textures->south))
		textures->south = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(textures->west))
		textures->west = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(textures->east))
		textures->east = get_texture_path(line, j + 2);
	else
		return (ERR);
	return (SUCCESS);
}

static int	ignore_whitespaces_get_info(t_data *data, char **file, int i, int j)
{
	while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\n')
		j++;
	if (ft_isprint(file[i][j]) && !ft_isdigit(file[i][j]))
	{
		
		if (file[i][j + 1] && ft_isalpha(file[i][j + 1]))
		{
			if (fill_direction_textures(&data->texinfo, file[i], j) == ERR)
				return (err_msg(data->map.path, ERR_TEX_INVALID, FAILURE));
			return (BREAK);
		}	
		else
		{
			if (fill_color_textures(data, &data->texinfo, file[i], j) == ERR)
				return (FAILURE);
			return (BREAK);
		}	
	}
	else if (ft_isdigit(file[i][j]))
	{
		if (create_map(data, file, i) == FAILURE)
			return (err_msg(data->map.path, ERR_INVALID_MAP, FAILURE));
		return (SUCCESS);
	}
	return (CONTINUE);
}

int	get_file_data(t_data *data, char **file)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			ret = ignore_whitespaces_get_info(data, file, i, j);
			if (ret == BREAK)
				break ;
			else if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
