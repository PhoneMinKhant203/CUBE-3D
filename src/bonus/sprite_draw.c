/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:00:18 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/08 12:33:40 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	init_spdraw(t_game *game, t_sprite *sp, t_spdraw *d)
{
	double	sp_x;
	double	sp_y;
	double	inv_det;
	double	trans_x;

	sp_x = sp->x - game->player.x;
	sp_y = sp->y - game->player.y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	trans_x = inv_det * (game->player.dir_y * sp_x
			- game->player.dir_x * sp_y);
	d->trans_y = inv_det * (-game->player.plane_y * sp_x
			+ game->player.plane_x * sp_y);
	if (d->trans_y <= 0.05)
		return (0);
	d->tex = game->tex.sprite[sp->frame % SP_FRAME];
	if (!d->tex || !d->tex->pixels)
		return (0);
	d->screen_x = (int)((G_WIDTH / 2) * (1 + trans_x / d->trans_y));
	d->height = (int)(G_HEIGHT / d->trans_y);
	d->width = d->height;
	return (d->height > 0);
}

static void	set_sprite_bounds(t_spdraw *d)
{
	d->origin_y = -d->height / 2 + G_HEIGHT / 2;
	d->origin_x = -d->width / 2 + d->screen_x;
	d->start_y = d->origin_y;
	d->end_y = d->height / 2 + G_HEIGHT / 2;
	d->start_x = d->origin_x;
	d->end_x = d->width / 2 + d->screen_x;
	if (d->start_y < 0)
		d->start_y = 0;
	if (d->end_y >= G_HEIGHT)
		d->end_y = G_HEIGHT - 1;
	if (d->start_x < 0)
		d->start_x = 0;
	if (d->end_x >= G_WIDTH)
		d->end_x = G_WIDTH - 1;
}

static void	draw_one_sprite(t_game *game, t_sprite *sp)
{
	t_spdraw	d;
	int			stripe;

	if (sp->isactive != 1)
		return ;
	if (!init_spdraw(game, sp, &d))
		return ;
	set_sprite_bounds(&d);
	stripe = d.start_x;
	while (stripe <= d.end_x)
	{
		draw_sprite_col(game, &d, stripe);
		stripe++;
	}
}

void	draw_sprites(t_game *game)
{
	int	i;

	sort_sprites(game);
	i = 0;
	while (i < SP_COUNT)
	{
		draw_one_sprite(game, &game->sprites[i]);
		i++;
	}
}
