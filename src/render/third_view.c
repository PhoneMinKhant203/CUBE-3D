/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:20:46 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/12 14:54:05 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	init_texline(t_game *game, t_ray *ray, t_texline *line)
{
	int	h;

	line->tex = get_tex(game, ray);
	if (!line->tex || !line->tex->pixels)
		return (0);
	if (line->tex->width == 0 || line->tex->height == 0)
		return (0);
	h = (int)(G_HEIGHT / ray->perp_wall_dt);
	if (h < 1)
		h = 1;
	line->start = -h / 2 + G_HEIGHT / 2;
	line->end = h / 2 + G_HEIGHT / 2;
	line->step = (double)line->tex->height / (double)h;
	line->pos = 0.0;
	if (line->start < 0)
	{
		line->pos = -line->start * line->step;
		line->start = 0;
	}
	if (line->end >= (int)G_HEIGHT)
		line->end = G_HEIGHT - 1;
	return (1);
}

static void	draw_tex_line(t_game *game, t_ray *ray, int x)
{
	t_texline		line;
	int				tex_x;
	int				tex_y;

	if (x < 0 || x >= (int)G_WIDTH)
		return ;
	if (!init_texline(game, ray, &line))
		return ;
	tex_x = get_tex_x(game, ray);
	while (line.start <= line.end)
	{
		tex_y = (int)line.pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)line.tex->height)
			tex_y = line.tex->height - 1;
		mlx_put_pixel(game->tex.img, x, line.start++,
			get_tex_color(line.tex, tex_x, tex_y));
		line.pos += line.step;
	}
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	if (ray->side == 'x')
		ray->perp_wall_dt = ray->side_dx - ray->delta_dx;
	else
		ray->perp_wall_dt = ray->side_dy - ray->delta_dy;
	if (ray->perp_wall_dt < 0.0001)
		ray->perp_wall_dt = 0.0001;
	draw_tex_line(game, ray, x);
}

void	draw_background(t_game *game)
{
	size_t	x;
	size_t	y;

	if (!game || !game->tex.img)
		return ;
	y = 0;
	while (y < G_HEIGHT)
	{
		x = 0;
		while (x < G_WIDTH)
		{
			if (y < G_HEIGHT / 2)
				mlx_put_pixel(game->tex.img, x, y, game->tex.ceiling);
			else
				mlx_put_pixel(game->tex.img, x, y, game->tex.floor);
			x++;
		}
		y++;
	}
}
