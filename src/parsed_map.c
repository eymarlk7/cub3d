#include    "../cub3d.h"

int	open_file(char *arg)
{
	int	fd;
	
	fd = open(arg, O_RDONLY);
	return (fd);
}

char	**get_map(int fd)
{

	char	*str;
	char	**map;
	char	*tmp_str;
	size_t	num_bytes;
	char	buffer[BUFFER_SIZE + 1];

	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	num_bytes = read(fd, buffer, BUFFER_SIZE);
	while (num_bytes > 0)
	{
		buffer[num_bytes] = '\0';
		tmp_str = ft_strjoin(str, buffer);
		free(str);
		str = tmp_str;
		num_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	map = ft_split(str, '\n');
	free(str);
	return (map);
}


int	init_map(t_data	*data, char *argv)
{
	int	fd;
	char	*file_name;

	if ((file_name = ft_strchr(argv, '.')))
	{
		if (ft_strcmp(file_name, ".cub") != 0)
			return (-1);
	}
	else
		return (ft_putstr_fd("error: extension file is wrong\n", 2), -1);
	if ((fd = open_file(argv)) == -1)
		return (ft_putstr_fd("error to open file\n", 2),-1);
	init_map_info(&data->map);
	init_texinfo(&data->texinfo);
	data->map.fd = fd;
	data->map.path = argv;
	data->map.file = get_map(fd);
	if (!data->map.file)
		return (ft_putstr_fd("map error\n", 2), -1);
	return (0);
}