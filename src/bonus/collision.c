/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:11:50 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/12 13:28:49 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_wall(t_game *game, int x, int y)
{
	int	row_len;

	if (!game->map || x < 0 || y < 0)
		return (1);
	if (!game->map[y])
		return (1);
	row_len = 0;
	while (game->map[y][row_len])
		row_len++;
	if (x >= row_len)
		return (1);
	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == DOOR_CLOSE)
		return (1);
	if (game->map[y][x] == ' ')
		return (1);
	return (0);
}

int	is_collision(t_game *game, double x, double y)
{
	if (is_wall(game, (int)floor(x - PLAYER_RADIUS),
			(int)floor(y - PLAYER_RADIUS)))
		return (1);
	if (is_wall(game, (int)floor(x + PLAYER_RADIUS),
			(int)floor(y - PLAYER_RADIUS)))
		return (1);
	if (is_wall(game, (int)floor(x - PLAYER_RADIUS),
			(int)floor(y + PLAYER_RADIUS)))
		return (1);
	if (is_wall(game, (int)floor(x + PLAYER_RADIUS),
			(int)floor(y + PLAYER_RADIUS)))
		return (1);
	return (0);
}
