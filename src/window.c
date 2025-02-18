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

int	close_window(t_hook *hook)
{
	t_vars	*vars;

	if (!hook || !hook->vars)
		exit(1);
	vars = hook->vars;
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (hook->map)
		free_map(hook->map);
	free(hook);
	exit(0);
}

int	key_hook(int keycode, t_hook *hook)
{
	if (keycode == 65307 || keycode == 53)
		close_window(hook);
	else if (keycode == 61 || keycode == 65451)
	{
		zoom_map(hook->map, 1.1);
		render_map(hook->map, hook->vars);
	}
	else if (keycode == 45 || keycode == 65453)
	{
		zoom_map(hook->map, 0.9);
		render_map(hook->map, hook->vars);
	}
	else if (keycode == 65362 || keycode == 65363
		|| keycode == 65364 || keycode == 65361)
		move_map(keycode, hook->map, hook->vars);
	return (0);
}

void	win_loop(t_vars *vars, t_map *map)
{
	t_hook	*hook;

	hook = malloc(sizeof(t_hook));
	if (!hook)
		return ;
	hook->vars = vars;
	hook->map = map;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_hook(vars->win, 17, 0, close_window, hook);
	mlx_hook(vars->win, 2, 1L << 0, key_hook, hook);
	mlx_loop(vars->mlx);
}
