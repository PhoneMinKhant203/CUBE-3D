/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:54:58 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/08 12:04:09 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

uint32_t	next_rng(t_game *game)
{
	game->rng = game->rng * 1103515245u + 12345u;
	return (game->rng);
}

static void	animate_sprite(t_game *game, t_sprite *sp)
{
	sp->timer += game->mlx->delta_time;
	if (sp->timer >= SP_ANIM_SPEED)
	{
		sp->timer = 0.0;
		sp->frame++;
		if (sp->frame >= SP_FRAME)
			sp->frame = 0;
	}
}

static void	move_sprite(t_game *game, t_sprite *sp)
{
	double	dx;
	double	dy;
	double	dist;
	double	step;

	dx = sp->target_x - sp->x;
	dy = sp->target_y - sp->y;
	dist = sqrt((dx * dx) + (dy * dy));
	if (dist < SP_REACH)
	{
		sp->isactive = 0;
		sp->delay = 2.0 + ((double)(next_rng(game) % 600) / 100.0);
		return ;
	}
	step = sp->speed * game->mlx->delta_time;
	if (step > dist)
		step = dist;
	sp->x += (dx / dist) * step;
	sp->y += (dy / dist) * step;
}

// It updates the position and animation of all sprites,
// and handles respawning if they are inactive
void	update_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < SP_COUNT)
	{
		if (game->sprites[i].isactive == 0)
		{
			game->sprites[i].delay -= game->mlx->delta_time;
			if (game->sprites[i].delay <= 0.0)
				respawn_sprite(game, &game->sprites[i]);
		}
		else
		{
			animate_sprite(game, &game->sprites[i]);
			move_sprite(game, &game->sprites[i]);
		}
		i++;
	}
}
