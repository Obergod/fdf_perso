/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:44:16 by mafioron          #+#    #+#             */
/*   Updated: 2025/01/30 18:44:23 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->points)
		free_points(map->points, map->height);
	free(map);
}

void	free_points(t_points **points, int height)
{
	int	i;

	if (!points)
		return ;
	i = 0;
	while (i < height)
	{
		if (points[i])
			free(points[i]);
		i++;
	}
	free(points);
}

void	init_line(t_line *line, t_points p1, t_points p2)
{
	line->dx = ft_abs(p2.x - p1.x);
	line->dy = -ft_abs(p2.y - p1.y);
	if (p1.x < p2.x)
		line->sx = 1;
	else
		line->sx = -1;
	if (p1.y < p2.y)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}

int	setup_buffers(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (1);
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "Ravachol");
	if (!vars->win)
	{
		free(vars->mlx);
		return (1);
	}
	vars->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!vars->img.img)
	{
		cleanup_vars(vars);
		return (1);
	}
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bits_per_pixel,
			&vars->img.line_length,
			&vars->img.endian);
	if (!vars->img.addr)
		cleanup_vars(vars);
	return (0);
}

void	init_map_data(t_map *map, char **map_str)
{
	int	i;

	i = 0;
	map->width = count_words(map_str[0], ' ');
	while (map_str[i])
		i++;
	map->height = i;
}
