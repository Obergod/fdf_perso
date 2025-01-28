/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:53:51 by mafioron          #+#    #+#             */
/*   Updated: 2025/01/22 19:54:01 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define ISO_ANGLE 0.523599f
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define SCALE 40

/*****			def of structs			*****/
typedef struct	s_data
{
	void	*img;
	char 	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
	t_data	img_front;
	t_data	img_back;
}	t_vars;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

typedef struct s_points
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_points;

typedef struct s_map
{
	t_points	**points;
	int			height;
	int			width;
}	t_map;



/*****		a trier			*****/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/*****		parsing			*****/
char		*get_all_file(int fd);
t_points	**init_points(char **map_str, int height, int width);
t_map		*get_data(int fd);

/*****		draw			*****/
void	init_line (t_line *line, int x0, int y0, int x1, int y1);
void	draw_line(t_data *img, t_points p1, t_points p2);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
void 	draw_map(t_map *map, t_data *data);

/*****	window management 	*****/
int	setup_buffers(t_vars *vars);

#endif
