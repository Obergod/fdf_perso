/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:51:48 by mafioron          #+#    #+#             */
/*   Updated: 2025/02/17 15:51:50 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_color(int z, t_map *map)
{
	double	percentage;
	int		r;
	int		g;
	int		b;

	if (map->z_max == map->z_min)
		return (0x0000FF);
	percentage = (double)(z - map->z_min) / (map->z_max - map->z_min);
	r = (int)(percentage * 255);
	b = (int)((1 - percentage) * 255);
	g = (int)((1 - fabs(2 * percentage - 1)) * 255);
	return ((r << 16) | (g << 8) | b);
}

void	set_colors(t_map *map)
{
	int	i;
	int	j;
	int	cur_z;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (!map->points[i][j].color)
			{
				cur_z = map->points[i][j].z;
				map->points[i][j].color = create_color(cur_z, map);
			}
		}
	}
}

int	get_z_color(char *nb, int *color)
{
	int		i;
	int		j;
	char	nb_res[16];
	int		res;

	if (!nb || !color)
		return (0);
	i = 0;
	if (nb[0] == '-')
		i++;
	j = 0;
	while (nb[i] && nb[i] != ',' && j < 15)
	{
		if (ft_isdigit(nb[i]))
			nb_res[j++] = nb[i];
		i++;
	}
	nb_res[j] = '\0';
	if (nb[i] == ',')
		*color = ft_atoi_base(nb + i + 3, "0123456789ABCDEF");
	res = ft_atoi(nb_res);
	if (nb[0] == '-')
		res = -res;
	return (res);
}

void	find_z_min_max(t_map *map)
{
	int	i;
	int	j;

	map->z_min = map->points[0][0].z;
	map->z_max = map->z_min;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->points[i][j].z < map->z_min)
				map->z_min = map->points[i][j].z;
			if (map->points[i][j].z > map->z_max)
				map->z_max = map->points[i][j].z;
		}
	}
	map->z_scale = map->z_max - map->z_min;
}
