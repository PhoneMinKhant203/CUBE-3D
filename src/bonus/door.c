/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:00:52 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/12 17:16:02 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	find_door(t_game *game, int *door_x, int *door_y)
{
	int		x;
	int		y;
	char	cell;

	x = (int)floor(game->player.x + game->player.dir_x);
	y = (int)floor(game->player.y + game->player.dir_y);
	cell = get_map_cell(game, x, y);
	if (cell == DOOR_CLOSE || cell == DOOR_OPEN)
	{
		*door_x = x;
		*door_y = y;
		return (1);
	}
	return (0);
}

void	update_door(t_game *game)
{
	int	pressed;
	int	door_x;
	int	door_y;

	pressed = mlx_is_key_down(game->mlx, MLX_KEY_F);
	if (pressed && !game->door_toggle)
	{
		if (find_door(game, &door_x, &door_y))
			init_door_anim(game, door_x, door_y);
	}
	game->door_toggle = pressed;
	if (!game->door.active)
	{
		update_auto_close(game);
		return ;
	}
	game->door.anim_timer += game->mlx->delta_time;
	if (game->door.anim_timer >= DOOR_ANIM_SPEED)
	{
		game->door.anim_timer = 0.0;
		game->door.frame += game->door.dir;
		if (game->door.frame >= DOOR_FRAME || game->door.frame < 0)
			stop_door_anim(game);
	}
}
