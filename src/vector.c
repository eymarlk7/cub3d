#include "../cub3d.h"

t_vec	create_vector(float y, float x)
{
	return((t_vec){y, x});
}

t_vec	sum_vector(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.y + v2.y, v1.x + v2.x});
}

t_vec	mult_vector(t_vec vector, float num)
{
	return ((t_vec){vector.y * num, vector.x * num});
}