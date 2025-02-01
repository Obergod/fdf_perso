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

void    cleanup_vars(t_vars *vars)
{
    if (vars->img.img)
        mlx_destroy_image(vars->mlx, vars->img.img);
    if (vars->win)
        mlx_destroy_window(vars->mlx, vars->win);
    if (vars->mlx)
        free(vars->mlx);
    exit(1);
}

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
		return (close(fd), 1);
	map  = get_data(fd);
	close(fd);
	if (!map)
	{
		cleanup_vars(&vars);
		return (1);
	}
	draw_map(map, &vars.img);
	win_loop(&vars, map);
	free_map(map);
	return (0);
}
