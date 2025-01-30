/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:44:16 by mafioron          #+#    #+#             */
/*   Updated: 2025/01/30 18:44:23 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->points)
		free_points(map->points, map->height);
	free(map);
}

void	free_points(t_points **points, int height)
{
	int	i;

	if (!points)
		return ;
	i = 0;
	while (i < height)
	{
		if (points[i])
			free(points[i]);
		i++;
	}
	free(points);
}
