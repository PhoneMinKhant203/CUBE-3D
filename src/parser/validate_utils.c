/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:17:01 by phonekha          #+#    #+#             */
/*   Updated: 2026/06/12 16:23:50 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_walkable(char c)
{
	return (c == '0' || c == DOOR_CLOSE || is_player(c));
}

static void	set_player_dir(t_game *game, char c)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = 0.0;
	if (c == 'N')
		game->player.dir_y = -1.0;
	else if (c == 'S')
		game->player.dir_y = 1.0;
	else if (c == 'E')
		game->player.dir_x = 1.0;
	else if (c == 'W')
		game->player.dir_x = -1.0;
}

static void	set_player_plane(t_game *game, char c)
{
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.0;
	if (c == 'N')
		game->player.plane_x = 0.66;
	else if (c == 'S')
		game->player.plane_x = -0.66;
	else if (c == 'E')
		game->player.plane_y = 0.66;
	else if (c == 'W')
		game->player.plane_y = -0.66;
}

void	set_player(t_game *game, int x, int y, char c)
{
	game->player.x = (double)x + 0.5;
	game->player.y = (double)y + 0.5;
	set_player_dir(game, c);
	set_player_plane(game, c);
	game->map[y][x] = '0';
}
