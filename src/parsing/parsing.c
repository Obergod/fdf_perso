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
			break ;
		stock = stock_extend(stock, line);
		if (!stock)
			return (NULL);
	}
	return (stock);
}

static t_points	*init_single_row(char **map_str, int row, int width)
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
	int			i;
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
	map->offset_x = 0;
	map->offset_y = 0;
}

t_map	*get_data(int fd)
{
	t_map	*map;
	char	**map_str;
	char	*file;

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
	init_map_data(map, map_str);
	map->points = init_points(map_str, map->height, map->width);
	if (!map->points)
		return (free_map(map), ft_free_split(map_str), NULL);
	find_z_min_max(map);
	set_colors(map);
	init_scale(map);
	ft_free_split(map_str);
	return (map);
}
