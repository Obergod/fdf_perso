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
	char	*buff;
	
	buff = NULL;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		buff = stock_extend(line, buff);
		free(line);
	}
	return (buff);
}

//void	init_coordinates()

t_points	**init_points(char **map_str, int height, int width)
{
	int	i;
	int	j;
	t_points	**points
	char	**map_split;

	points = (t_points **)malloc(sizeof(t_points *) * height);
	if (!points)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		j = -1;
		points[i] = (t_points *)malloc(sizeof(t_points) * width);
		if (!points)
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
			points[i][j].z = ft_atoi(map_str[j]);
			color = 0xFFFFFF; 
		}
		ft_free_split(map_split);	
	}
	return (points);
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
		return (null);
	file = get_all_file(fd);
	if (!file)
		return (free(map), NULL);
	//check errors()
	map_str = ft_split(file, '\n');
	free(file);
	if (!map_str)
		return (NULL);
	map->width = ft_count_words(map.map[i]);
	while (map.map[i])
		i++;
	map->height = i;
	map->points = init_points(map_str, map->height, map->width);
	free(map_str);
	return (map);
}
