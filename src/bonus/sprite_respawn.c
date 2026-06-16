/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_respawn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:43:53 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/08 15:56:45 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_sprite_cell(t_game *game, int x, int y)
{
	double	dx;
	double	dy;
	char	c;

	c = get_map_cell(game, x, y);
	if (!(c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		return (0);
	dx = ((double)x + 0.5) - game->player.x;
	dy = ((double)y + 0.5) - game->player.y;
	if ((dx * dx) + (dy * dy) < SP_DIST * SP_DIST)
		return (0);
	return (1);
}

static int	process_sprite_map(t_game *game, int target, double *x, double *y)
{
	int	mx;
	int	my;
	int	count;

	my = -1;
	count = 0;
	while (game->map && game->map[++my])
	{
		mx = -1;
		while (game->map[my][++mx])
		{
			if (is_sprite_cell(game, mx, my))
			{
				count++;
				if (count == target && x && y)
				{
					*x = (double)mx + 0.5;
					*y = (double)my + 0.5;
					return (count);
				}
			}
		}
	}
	return (count);
}

static int	pick_sprite_pos(t_game *game, double *x, double *y)
{
	int	count;

	count = process_sprite_map(game, -1, NULL, NULL);
	if (count <= 0)
		return (0);
	process_sprite_map(game, next_rng(game) % count, x, y);
	return (1);
}

static double	dist_sq(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return ((dx * dx) + (dy * dy));
}

void	respawn_sprite(t_game *game, t_sprite *sp)
{
	double	tx;
	double	ty;
	int		i;

	if (!pick_sprite_pos(game, &sp->x, &sp->y))
		return ;
	tx = sp->x;
	ty = sp->y;
	i = 0;
	while (i < 8 && dist_sq(sp->x, sp->y, tx, ty) < 9.0)
	{
		if (!pick_sprite_pos(game, &tx, &ty))
			return ;
		i++;
	}
	sp->target_x = tx;
	sp->target_y = ty;
	sp->speed = 0.45 + ((double)(next_rng(game) % 70) / 100.0);
	sp->frame = 0;
	sp->timer = 0.0;
	sp->isactive = 1;
}
