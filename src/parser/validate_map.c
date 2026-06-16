/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:16:38 by phonekha          #+#    #+#             */
/*   Updated: 2026/06/12 16:23:50 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == DOOR_CLOSE
		|| is_player(c));
}

static int	is_cell_closed(t_game *game, int x, int y)
{
	if (get_map_cell(game, x, y) == ' ')
		return (0);
	return (1);
}

static int	check_neighbors(t_game *game, int x, int y)
{
	int	dx;
	int	dy;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if ((dx != 0 || dy != 0) && !is_cell_closed(game, x + dx, y + dy))
				return (0);
			dx++;
		}
		dy++;
	}
	return (1);
}

static int	validate_cell(t_game *game, int x, int y, int *players)
{
	char	c;

	c = game->map[y][x];
	if (!is_valid_char(c))
	{
		ft_putstr_fd("Error\nInvalid map character\n", 2);
		return (0);
	}
	if (is_walkable(c) && !check_neighbors(game, x, y))
	{
		ft_putstr_fd("Error\nMap is not closed\n", 2);
		return (0);
	}
	if (is_player(c))
	{
		(*players)++;
		set_player(game, x, y, c);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	y = 0;
	while (game->map && game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!validate_cell(game, x, y, &players))
				return (0);
			x++;
		}
		y++;
	}
	if (players != 1)
	{
		ft_putstr_fd("Error\nMap needs exactly one player\n", 2);
		return (0);
	}
	return (1);
}
