/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:33:39 by mafioron          #+#    #+#             */
/*   Updated: 2025/01/30 18:33:41 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_transform(t_points *p, t_map *map)
{
	double old_x;
	double old_y;
	double old_z;

	old_x = p->x * map->scale;
	old_y = p->y * map->scale;
	old_z = (double)p->z * map->z_scale;
	p->x = (int)((old_x - old_y) * cos(ISO_ANGLE)) + WIN_WIDTH / 2;
	p->y = (int)((old_x + old_y) * sin(ISO_ANGLE) - old_z) + WIN_HEIGHT / 3;
}
