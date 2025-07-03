#include "../cub3d.h"

int     get_player_pos(t_player *player, char **map)
{
        int     y;
        int     x;

        y = 0;
        while (map[y])
        {
                x = 0;
                while (map[y][x])
                {
                        if (map[y][x] == 'N' || map[y][x] == 'S'||
                        map[y][x] == 'E' || map[y][x] == 'W')
                        {
                                player->pos = create_vector((float)y + .5, (float)x + .5);
                                return (1);
                        }
                        x++;
                }
                y++;
        }
        return (-1);
}

int     get_player_dir(t_player *player, char **map)
{
        int     y;
        int     x;

        y = 0;
        while (map[y])
        {
                x = 0;
                while (map[y][x])
                {
                        if (map[y][x] == 'N')
                        {
                                player->dir = create_vector(-1, 0);
                                player->camera_plane = create_vector(0, 0.66);
                                map[y][x] = '0';
                                return (1);
                        }
                        else if (map[y][x] == 'S')
                        {
                                player->dir = create_vector(1, 0);
                                player->camera_plane = create_vector(0, -0.66);
                                map[y][x] = '0';
                                return (1);
                        }
                          else if (map[y][x] == 'E')
                        {
                                player->dir = create_vector(0, -1);
                                player->camera_plane = create_vector(0.66, 0);
                                map[y][x] = '0';
                                return (1);
                        }
                          else if (map[y][x] == 'W')
                        {
                                player->dir = create_vector(0, 1);
                                player->camera_plane = create_vector(-0.66, 0);
                                map[y][x] = '0';
                                return (1);
                        }
                        x++;
                }
                y++;
        }
        return (-1);
}
