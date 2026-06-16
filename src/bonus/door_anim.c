/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:03:34 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/12 17:17:28 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	can_close_door(t_game *game, int x, int y)
{
	set_map_cell(game, x, y, DOOR_CLOSE);
	if (is_collision(game, game->player.x, game->player.y))
	{
		set_map_cell(game, x, y, DOOR_OPEN);
		return (0);
	}
	set_map_cell(game, x, y, DOOR_OPEN);
	return (1);
}

static void	door_closing(t_game *game)
{
	t_door	*door;

	door = &game->door;
	if (door->active)
		return ;
	if (get_map_cell(game, door->x, door->y) != DOOR_OPEN)
		return ;
	if (!can_close_door(game, door->x, door->y))
	{
		door->open_time = 1.0;
		return ;
	}
	door->frame = DOOR_FRAME - 1;
	door->dir = -1;
	door->anim_timer = 0.0;
	door->active = 1;
	set_map_cell(game, door->x, door->y, DOOR_CLOSE);
}

void	stop_door_anim(t_game *game)
{
	if (game->door.dir == 1)
	{
		set_map_cell(game, game->door.x,
			game->door.y, DOOR_OPEN);
		game->door.open_time = DOOR_AUTO_TIMER;
	}
	else
	{
		set_map_cell(game, game->door.x,
			game->door.y, DOOR_CLOSE);
		game->door.open_time = 0.0;
	}
	game->door.active = 0;
}

void	init_door_anim(t_game *game, int x, int y)
{
	char	cell;

	if (game->door.active)
		return ;
	cell = get_map_cell(game, x, y);
	if (cell == DOOR_CLOSE)
	{
		game->door.x = x;
		game->door.y = y;
		game->door.frame = 0;
		game->door.dir = 1;
		game->door.anim_timer = 0.0;
		game->door.active = 1;
	}
	else if (cell == DOOR_OPEN && can_close_door(game, x, y))
	{
		game->door.x = x;
		game->door.y = y;
		game->door.frame = DOOR_FRAME - 1;
		game->door.dir = -1;
		game->door.anim_timer = 0.0;
		game->door.active = 1;
		set_map_cell(game, x, y, DOOR_CLOSE);
	}
}

void	update_auto_close(t_game *game)
{
	t_door	*door;

	door = &game->door;
	if (door->active)
		return ;
	if (door->open_time <= 0.0)
		return ;
	if (get_map_cell(game, door->x, door->y) != DOOR_OPEN)
	{
		door->open_time = 0.0;
		return ;
	}
	door->open_time -= game->mlx->delta_time;
	if (door->open_time <= 0.0)
		door_closing(game);
}
