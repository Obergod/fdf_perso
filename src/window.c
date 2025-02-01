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

void	win_loop(t_vars *vars, t_map *map)
{
	t_hook *hook;

	hook = malloc(sizeof(t_hook));
	if (!hook)
		return ;
	hook->vars = vars;
	hook->map = map;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_hook(vars->win, 17, 0, close_window, hook);
	mlx_hook(vars->win, 2, 1L<<0, key_hook, hook);
	mlx_loop(vars->mlx);
}

int	close_window(t_hook *hook)
{
	t_vars *vars;
	if (!hook || !hook->vars)
		exit(1);
	vars = hook->vars;
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	free(hook);
	exit(0);
}

int	key_hook(int keycode, t_hook *hook)
{
	printf("key : %d\n", keycode);
	if (keycode == 65307 || keycode == 53)
		close_window(hook);
	else if (keycode == 61 || keycode == 65451)
	{
		hook->map->zoom *= 1.1;
		render_map(hook->map, hook->vars);
	}
	else if (keycode == 45 || keycode == 65453)
	{
		hook->map->zoom *= 0.9;
		render_map(hook->map, hook->vars);
	}
	else if (keycode == 65362 || keycode == 65361 ||
			keycode == 65364 || keycode == 365361)
		move_map(keycode, hook->map, hook->vars);
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
	t_points corner;
    
    corner.x = map->width - 1;
    corner.y = map->height - 1;
    corner.z = map->points[map->height-1][map->width-1].z;
    
    iso_transform(&corner, map);
    if (corner.x >= WIN_WIDTH || corner.y >= WIN_HEIGHT)
    {
		if (map->zoom > 1.0)
        	map->zoom *= 0.9;
        return;
    }

	clear_image(&vars->img);
	draw_map(map, &vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	move_map(int keycode, t_map *map, t_vars *vars)
{
	if (keycode == 65362)
		map->offset_y -= 10;
	if (keycode == 65364)
		map->offset_y += 10;
	if (keycode == 65363)
		map->offset_x -= 10;
	if (keycode == 65361)
		map->offset_x += 10;
	render_map(map, vars);
}
