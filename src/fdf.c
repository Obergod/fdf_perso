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
    printf("2. Zoom after get_data: %f\n", map->zoom);
	close(fd);
	if (!map)
	{
		close_window(&vars);
		return (1);
	}
	draw_map(map, &vars.img);
	printf("3. Zoom after setting vars.map: %f\n", map->zoom);
	free_map(map);
	win_loop(vars);
	return (0);
}
