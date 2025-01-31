/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:28:39 by mafioron          #+#    #+#             */
/*   Updated: 2025/01/27 15:28:44 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*get_all_file(int fd)
{
	char	*line;
	char	*stock;
	
	stock = NULL;
	if (fd < 0)
		return (NULL);
	
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		stock = stock_extend(stock, line);
		if (!stock)
			return (NULL);
	}
	return (stock);
}

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

static t_points *init_single_row(char **map_str, int row, int width)
{
	t_points	*points;
	char		**split;
	int			col;

	points = malloc(sizeof(t_points) * width);
	if (!points)
		return (NULL);
	split = ft_split(map_str[row], ' ');
	if (!split)
		return (free(points), NULL);
	col = -1;
	while (++col < width)
	{
		points[col].y = row;
		points[col].x = col;
		points[col].color = 0;
		points[col].z = get_z_color(split[col], &points[col].color);
	}
	ft_free_split(split);
	return (points);
}

t_points	**init_points(char **map_str, int height, int width)
{
	int	i;
	t_points	**points;

	points = (t_points **)malloc(sizeof(t_points *) * height);
	if (!points)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		points[i] = init_single_row(map_str, i, width);
		if (!points[i])
			return (free_points(points, height), NULL);
	}
	return (points);
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

void	init_scale(t_map *map)
{
	double	scale_x;
	double	scale_y;

	scale_x = (WIN_WIDTH * 0.7) / (map->width + map->height);
	scale_y = (WIN_HEIGHT * 0.7) / (map->width + map->height);
	if (scale_x < scale_y)
		map->scale = scale_x;
	else
		map->scale = scale_y;
	if (map->z_scale > 0)
		map->z_scale = map->scale / ((map->z_scale) * 0.3);
	else
		map->z_scale = map->scale / 4;
	map->zoom = 1.0;
    printf("Zoom initialized to: %f\n", map->zoom);  // Debug print
}

t_map	*get_data(int fd)
{
	t_map	*map;
	char	**map_str;
	char	*file;
	int		i;

	i = 0;
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	file = get_all_file(fd);
	if (!file)
		return (free_map(map), NULL);
	map_str = ft_split(file, '\n');
	free(file);
	if (!map_str)
		return (free_map(map), NULL);
	map->width = count_words(map_str[0], ' ');
	while (map_str[i])
		i++;
	map->height = i;
	map->points = init_points(map_str, map->height, map->width);
	if (!map->points)
		return (free_map(map), ft_free_split(map_str), NULL);
	find_z_min_max(map);
	set_colors(map);
	init_scale(map);
	ft_free_split(map_str);
	return (map);
}

