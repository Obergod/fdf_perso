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

int	setup_buffers(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (1);
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "Ravachol");
	
	vars->img_front.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->img_back.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!vars->img_front.img || !vars->img_back.img)
		return (1);
	vars->img_front.addr = mlx_get_data_addr(vars->img_front.img,
								&vars->img_front.bits_per_pixel,
								&vars->img_front.line_length,
								&vars->img_front.endian);
	vars->img_back.addr = mlx_get_data_addr(vars->img_back.img,
								&vars->img_back.bits_per_pixel,
								&vars->img_back.line_length,
								&vars->img_back.endian);
	return (0);
}

int	close_window(t_vars *vars)
{
	if (vars->img_front.img)
		mlx_destroy_image(vars->mlx, vars->img_front.img);
	if (vars->img_back.img)
		mlx_destroy_image(vars->mlx, vars->img_back.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	exit(0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307 || keycode == 53)
		close_window(vars);
	return (0);
}
