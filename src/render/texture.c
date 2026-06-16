/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 02:46:38 by phonekha          #+#    #+#             */
/*   Updated: 2026/06/12 14:23:55 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	clamp_tex_coord(int value, uint32_t max)
{
	if (value < 0)
		return (0);
	if (value >= (int)max)
		return ((int)max - 1);
	return (value);
}

uint32_t	get_tex_color(mlx_texture_t *tex, int tex_x, int tex_y)
{
	size_t	index;
	uint8_t	*p;

	if (!tex || !tex->pixels || tex->bytes_per_pixel < 4)
		return (0x000000FF);
	if (tex->width == 0 || tex->height == 0)
		return (0x000000FF);
	tex_x = clamp_tex_coord(tex_x, tex->width);
	tex_y = clamp_tex_coord(tex_y, tex->height);
	index = (tex_y * tex->width + tex_x) * tex->bytes_per_pixel;
	p = &tex->pixels[index];
	return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static mlx_texture_t	*get_door_tex(t_game *game, t_ray *ray)
{
	int	frame;

	frame = 0;
	if (game->door.active
		&& game->door.x == ray->map_x
		&& game->door.y == ray->map_y)
		frame = game->door.frame;
	if (frame < 0)
		frame = 0;
	if (frame >= DOOR_FRAME)
		frame = DOOR_FRAME - 1;
	if (!game->tex.door[frame])
		return (game->tex.door[0]);
	return (game->tex.door[frame]);
}

mlx_texture_t	*get_tex(t_game *game, t_ray *ray)
{
	if (ray->hit == DOOR_CLOSE)
		return (get_door_tex(game, ray));
	if (ray->side == 'x')
	{
		if (ray->dir_x > 0)
			return (game->tex.west);
		return (game->tex.east);
	}
	else
	{
		if (ray->dir_y > 0)
			return (game->tex.north);
		return (game->tex.south);
	}
}

// draw the vertical line of the wall with texture mapping
// handle the texture flipping for different wall sides and ray directions
int	get_tex_x(t_game *game, t_ray *ray)
{
	double			wall_x;
	int				tex_x;
	mlx_texture_t	*tex;

	tex = get_tex(game, ray);
	if (!tex || tex->width == 0)
		return (0);
	if (ray->side == 'x')
		wall_x = game->player.y + ray->perp_wall_dt * ray->dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dt * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	if ((ray->side == 'x' && ray->dir_x < 0)
		|| (ray->side == 'y' && ray->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
