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


int	main (int ac, char **av)
{
	t_vars	vars;
	int		error;
	t_map	*map;
	int		fd;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	error = setup_buffers(&vars);
	if (error)
		return (1);
	map  = get_data(fd);
	if (!map)
		return (1);
	draw_map(map, &vars.img_front);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img_front.img, 0, 0);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
