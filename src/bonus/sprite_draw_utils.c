/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:22:49 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/16 15:44:54 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	insertion_sort(t_sprite *sp, int size)
{
	int			i;
	int			j;
	t_sprite	key;

	if (!sp || size <= 1)
		return ;
	i = 1;
	while (i < size)
	{
		key = sp[i];
		j = i - 1;
		while (j >= 0 && sp[j].dist < key.dist)
		{
			sp[j + 1] = sp[j];
			j--;
		}
		sp[j + 1] = key;
		i++;
	}
}

// This sorts the sprites in descending order of distance from the player
// For correct rendering of overlapping sprites
// Without sorting,
// farther sprites may be drawn over closer ones, causing visual glitches
void	sort_sprites(t_game *game)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < SP_COUNT)
	{
		dx = game->sprites[i].x - game->player.x;
		dy = game->sprites[i].y - game->player.y;
		game->sprites[i].dist = (dx * dx) + (dy * dy);
		i++;
	}
	insertion_sort(game->sprites, SP_COUNT);
}

static int	get_sp_tex_pos(int cur, int org, int size, int tsize)
{
	int	coord;

	if (size == 0)
		return (0);
	coord = (int)((((double)(cur - org)) * tsize) / (double)size);
	if (coord < 0)
		return (0);
	if (coord >= tsize)
		return (tsize - 1);
	return (coord);
}

void	draw_sprite_col(t_game *game, t_spdraw *d, int stripe)
{
	uint32_t	color;
	int			tex_x;
	int			tex_y;
	int			y;

	if (stripe < 0 || stripe >= G_WIDTH)
		return ;
	if (d->trans_y >= game->z_buffer[stripe])
		return ;
	tex_x = get_sp_tex_pos(stripe, d->origin_x, d->width, d->tex->width);
	y = d->start_y;
	while (y <= d->end_y)
	{
		tex_y = get_sp_tex_pos(y, d->origin_y, d->height, d->tex->height);
		color = get_tex_color(d->tex, tex_x, tex_y);
		if ((color & 0xFF) > 20)
			mlx_put_pixel(game->tex.img, stripe, y, color);
		y++;
	}
}
