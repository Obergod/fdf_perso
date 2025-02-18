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

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>

# define ISO_ANGLE 0.523599
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define SCALE 40

/*****			def of structs			*****/
typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_data		img;
}				t_vars;

typedef struct s_line
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
}				t_line;

typedef struct s_points
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_points;

typedef struct s_map
{
	t_points	**points;
	int			height;
	int			width;
	double		scale;
	double		z_scale;
	int			z_min;
	int			z_max;
	double		zoom;
	int			offset_x;
	int			offset_y;
}				t_map;

typedef struct s_hook
{
	t_vars		*vars;
	t_map		*map;
}				t_hook;

/*****		a trier			*****/
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			free_points(t_points **points, int height);
void			free_map(t_map *map);
void			iso_transform(t_points *p, t_map *map);
void			find_z_min_max(t_map *map);
int				get_z_color(char *nb, int *color);

/*****		parsing			*****/
char			*get_all_file(int fd);
t_points		**init_points(char **map_str, int height, int width);
t_map			*get_data(int fd);
void			free_map(t_map *map);
void			free_points(t_points **points, int height);
void			set_colors(t_map *map);
void			init_map_data(t_map *map, char **map_str);

/*****		draw			*****/
void			init_line(t_line *line, t_points p1, t_points p2);
void			draw_line(t_data *img, t_points p1, t_points p2);
void			my_mlx_pixel_put(t_data *img, int x, int y, int color);
void			draw_map(t_map *map, t_data *data);
void			render_map(t_map *map, t_vars *vars);

/*****	window management 	*****/
int				setup_buffers(t_vars *vars);
int				close_window(t_hook *hook);
int				key_hook(int keycode, t_hook *hook);
void			win_loop(t_vars *vars, t_map *map);
void			cleanup_vars(t_vars *vars);
void			move_map(int keycode, t_map *map, t_vars *vars);
void			zoom_map(t_map *map, double zoom_factor);

#endif
