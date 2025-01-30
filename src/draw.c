/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:18:04 by mafioron          #+#    #+#             */
/*   Updated: 2025/01/28 16:18:05 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	draw_line(t_data *img, t_points p1, t_points p2)
{
	t_line	line;
	int		e2;

	init_line(&line, p1.x, p1.y, p2.x, p2.y);
	while (1)
	{
		my_mlx_pixel_put(img, p1.x, p1.y, p1.color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = line.err * 2;
		if (e2 >= line.dy)
		{
			p1.x += line.sx;
			line.err += line.dy;
		}
		if (e2 <= line.dx)
		{
			p1.y += line.sy;
			line.err += line.dx;
		}
	}
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_map(t_map *map, t_data *data)
{
	int	i;
	int	j;
	t_points p1;
	t_points p2;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			p1 = map->points[i][j];
			iso_transform(&p1, map);
			if (j < map->width - 1)
			{
				p2 = map->points[i][j + 1];
				iso_transform(&p2, map);
				draw_line(data, p1, p2);
			}
			if (i < map->height - 1)
			{
				p2 = map->points[i + 1][j];
				iso_transform(&p2, map);
				draw_line(data, p1, p2);
			}
		}
	}
}
