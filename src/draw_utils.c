/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:55:35 by mafioron          #+#    #+#             */
/*   Updated: 2025/02/17 16:55:36 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			my_mlx_pixel_put(img, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

void	render_map(t_map *map, t_vars *vars)
{
	clear_image(&vars->img);
	draw_map(map, &vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	zoom_map(t_map *map, double zoom_factor)
{
	double	old_zoom;

	old_zoom = map->zoom;
	map->zoom *= zoom_factor;
	map->offset_x = (int)(map->offset_x * map->zoom / old_zoom);
	map->offset_y = (int)(map->offset_y * map->zoom / old_zoom);
}

void	move_map(int keycode, t_map *map, t_vars *vars)
{
	if (keycode == 65362)
		map->offset_y -= 10;
	if (keycode == 65364)
		map->offset_y += 10;
	if (keycode == 65363)
		map->offset_x += 10;
	if (keycode == 65361)
		map->offset_x -= 10;
	render_map(map, vars);
}
