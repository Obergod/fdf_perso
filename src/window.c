/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:49:07 by mafioron          #+#    #+#             */
/*   Updated: 2025/01/29 18:49:11 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	win_loop(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_hook(vars->win, 17, 0, close_window, &vars);
	mlx_hook(vars->win, 2, 1L<<0, key_hook, &vars);
	mlx_loop(vars->mlx);
}

int	close_window(t_vars *vars)
{
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	exit(0);
}

int	key_hook(int keycode, t_vars *vars, t_map *map)
{
	if (keycode == 65307 || keycode == 53)
		close_window(vars);
	else if (keycode == 61 || keycode == 65451)
	{	
        printf("Before zoom: %f\n", map->zoom);
		map->zoom *= 1.1;
		render_map(map, vars);
		printf("after zoom: %f\n", map->zoom);
	}
	else if(keycode == 45 || keycode == 65453)
	{
		map->zoom *= 0.9;
		render_map(map, vars);
	}
	return (0);
}

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
