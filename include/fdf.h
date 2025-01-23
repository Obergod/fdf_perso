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

# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"

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

/*****		a trier			*****/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);


#endif
