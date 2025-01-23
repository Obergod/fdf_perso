/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:06:08 by mafioron          #+#    #+#             */
/*   Updated: 2025/01/22 17:06:10 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1080)
	{
		j = 0;
		while (j < 1920)
		{
			my_mlx_pixel_put(img, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

/*
void	render_frame(t_vars *vars)
{
	t_data	temp;

	clear_image(&vars->img_back);
	draw_stuff(&vars->img_back);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_back.img, 0, 0);
	temp = vars->img_front;
	vars->img_front = vars->img_back;
	vars->img_back = temp;
}
*/
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

void	draw_line(t_data *img, int	x0, int y0, int	x1, int y1)
{
	t_line	line;
	int		e2;

	init_line(&line, x0, y0, x1, y1);
	while (1)
	{
		my_mlx_pixel_put(img, x0, y0, 0xFFFFFF);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = line.err * 2
		if (e2 >= line.dy)
		{
			x0 += line.sx;
			line.err += line.dy;
		}
		if (e2 <= line.dx)
		{
			y0 += line.sy;
			line.err += line.dx
		}
	}
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	setup_buffers(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars)
		return (1);
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "Ravachol");
	
	vars->img_front.img = mlx_new_image(vars->mlx, 1920, 1080);
	vars->img_back.img = mlx_new_image(vars->mlx, 1920, 1080);
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


int	main (int ac, char **av)
{
	t_vars	vars;
	int		error;
	
	error = setup_buffers(&vars);
	if (error)
		return (1);
	my_mlx_pixel_put(&vars.img_front, 500, 500, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img_front.img, 0, 0);
	mlx_loop(vars.mlx);

	return (0);
}
