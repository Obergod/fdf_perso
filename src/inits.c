/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:06:36 by mafioron          #+#    #+#             */
/*   Updated: 2025/01/29 16:06:36 by mafioron         ###   ########.fr       */
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
