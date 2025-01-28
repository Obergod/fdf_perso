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

void	init_line (t_line *line, int x0, int y0, int x1, int y1)
{
	line->dx = ft_abs(x1 - x0);
	line->dy = -ft_abs(y1 - y0);
	if (x0 < x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (y0 < y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}

void	center_scale_line(t_points *p1, t_points *p2)
{
	p1->x = p1->x * SCALE + WIN_WIDTH / 2;
	p1->y = p1->y * SCALE + WIN_HEIGHT / 3;
	//p1->z = p1->z * SCALE / 3;
	p2->x = p2->x * SCALE + WIN_WIDTH / 2;
	p2->y = p2->y * SCALE + WIN_HEIGHT / 3;
	//p2->z = p2->z * SCALE / 3;
}

void	draw_line(t_data *img, t_points p1, t_points p2)
{
	t_line	line;
	int		e2;

	center_scale_line(&p1, &p2);
	printf("Line from (%d,%d) to (%d,%d)\n", p1.x, p1.y, p2.x, p2.y);
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

void	iso_transform(t_points *p)
{
	int	old_x;
	int	old_y;

	old_x = p->x;
	old_y = p->y;
	p->x = (old_x - old_y) * cosf(ISO_ANGLE);
	p->y = (old_x + old_y) * sinf(ISO_ANGLE) - p->z;
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
			iso_transform(&p1);
		/*	center_scale_line(&p1, &p2);
			my_mlx_pixel_put(data, p1.x, p1.y, p1.color);*/
			if (j < map->width - 1)
			{
				p2 = map->points[i][j + 1];
				iso_transform(&p2);
				draw_line(data, p1, p2);
			}
			if (i < map->height - 1)
			{
				p2 = map->points[i + 1][j];
				iso_transform(&p2);
				draw_line(data, p1, p2);
			}
		}
	}
}
