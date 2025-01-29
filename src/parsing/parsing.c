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
	}
	return (stock);
}

//void	init_coordinates()

t_points	**init_points(char **map_str, int height, int width)
{
	int	i;
	int	j;
	t_points	**points;
	char	**map_split;

	points = (t_points **)malloc(sizeof(t_points *) * height);
	if (!points)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		j = -1;
		points[i] = (t_points *)malloc(sizeof(t_points) * width);
		if (!points[i])
		{
			//free points[i] function;
			return (free(points), NULL);
		}
		map_split = ft_split(map_str[i], ' ');
		if (!map_split)
			return (NULL);
		while (++j < width)
		{
			points[i][j].y = i; 
			points[i][j].x = j;
			points[i][j].z = ft_atoi(map_split[j]);
			points[i][j].color = 0xFFFFFF; 
		}
		ft_free_split(map_split);	
	}
	return (points);
}

int	find_z_range(t_map *map)
{
	int	i;
	int	j;
	int	z_min;
	int	z_max;

	z_min = map->points[0][0].z;
	z_max = z_min;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->points[i][j].z < z_min)
				z_min = map->points[i][j].z;
			if (map->points[i][j].z > z_max)
				z_max = map->points[i][j].z;
		}
	}
	return (z_max - z_min);
}

void	init_scale(t_map *map)
{
	double	scale_x;
	double	scale_y;
	int		z_range;

	z_range = find_z_range(map);
	scale_x = (WIN_WIDTH * 0.7) / (map->width + map->height);
	scale_y = (WIN_HEIGHT * 0.7) / (map->width + map->height);
	if (scale_x < scale_y)
		map->scale = scale_x;
	else
		map->scale = scale_y;
	if (z_range > 0)
		map->z_scale = map->scale / (z_range * 0.3);
	else
		map->z_scale = map->scale / 4;
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
		return (free(map), NULL);
	map_str = ft_split(file, '\n');
	free(file);
	if (!map_str)
		return (free(map), NULL);
	map->width = count_words(map_str[0], ' ');
	while (map_str[i])
		i++;
	map->height = i;
	map->points = init_points(map_str, map->height, map->width);
	init_scale(map);
	ft_free_split(map_str);
	if (!map->points)
		return (free(map), NULL);
	return (map);
}

