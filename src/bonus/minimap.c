/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 13:24:02 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/12 13:28:49 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	draw_maptile(t_game *game, int x, int y, double origin[2])
{
	char	cell;
	int		map[2];
	int		screen[2];

	map[0] = (int)floor(origin[0]) + x;
	map[1] = (int)floor(origin[1]) + y;
	cell = get_map_cell(game, map[0], map[1]);
	if (cell == ' ')
		return ;
	screen[0] = MINI_MARGIN + (int)((map[0] - origin[0]) * MINI_SCALE);
	screen[1] = MINI_MARGIN + (int)((map[1] - origin[1]) * MINI_SCALE);
	if (cell == DOOR_CLOSE)
		draw_square(game, screen[0], screen[1], MINI_DOOR);
	else if (cell == '1')
		draw_square(game, screen[0], screen[1], MINI_WALL);
	else
		draw_square(game, screen[0], screen[1], MINI_FLOOR);
}

static void	draw_player_dir(t_game *game, int px, int py)
{
	double	rx;
	double	ry;
	int		len;
	int		side;
	char	cell;

	len = 0;
	while (len < RADAR_LEN)
	{
		side = -(int)(len * RADAR_WIDTH);
		while (side <= (int)(len * RADAR_WIDTH))
		{
			rx = game->player.dir_x * len + (-game->player.dir_y) * side;
			ry = game->player.dir_y * len + game->player.dir_x * side;
			cell = get_map_cell(game, (int)(game->player.x + rx / MINI_SCALE),
					(int)(game->player.y + ry / MINI_SCALE));
			if (cell == '1' || cell == ' ')
				break ;
			put_pixel(game, px + (int)rx, py + (int)ry, MINI_DIR);
			side++;
		}
		len++;
	}
}

static void	draw_player(t_game *game)
{
	int	px;
	int	py;
	int	size;

	size = (MINI_SCALE - 1) / 2;
	px = MINI_MARGIN + (MINI_WIDTH * MINI_SCALE) / 2;
	py = MINI_MARGIN + (MINI_HEIGHT * MINI_SCALE) / 2;
	draw_square(game, px - size, py - size, MINI_PLAYER);
	draw_player_dir(game, px, py);
}

void	draw_minimap(t_game *game)
{
	double	origin[2];
	int		x;
	int		y;

	origin[0] = game->player.x - ((double)MINI_WIDTH / 2.0);
	origin[1] = game->player.y - ((double)MINI_HEIGHT / 2.0);
	draw_square(game, MINI_MARGIN, MINI_MARGIN, MINI_BG);
	y = 0;
	while (y < MINI_HEIGHT + 1)
	{
		x = 0;
		while (x < MINI_WIDTH + 1)
		{
			draw_maptile(game, x, y, origin);
			x++;
		}
		y++;
	}
	draw_player(game);
}
