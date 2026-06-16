/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phonekha <phonekha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:57:51 by phonekha          #+#    #+#             */
/*   Updated: 2026/06/11 13:58:08 by phonekha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_map_width(t_game *game)
{
	int	i;
	int	width;
	int	row_len;

	if (!game || !game->map)
		return (0);
	i = 0;
	width = 0;
	while (game->map[i])
	{
		row_len = ft_strlen(game->map[i]);
		if (row_len > width)
			width = row_len;
		i++;
	}
	return (width);
}

int	get_map_height(t_game *game)
{
	int	height;

	height = 0;
	if (!game->map)
		return (0);
	while (game->map[height])
		height++;
	return (height);
}

void	set_map_cell(t_game *game, int x, int y, char value)
{
	int	row_len;

	if (!game || !game->map || y < 0 || x < 0)
		return ;
	if (y >= get_map_height(game))
		return ;
	row_len = ft_strlen(game->map[y]);
	if (x >= row_len)
		return ;
	game->map[y][x] = value;
}

char	get_map_cell(t_game *game, int x, int y)
{
	int	row_len;

	if (!game || !game->map || y < 0 || x < 0)
		return (' ');
	if (y >= get_map_height(game))
		return (' ');
	row_len = ft_strlen(game->map[y]);
	if (x >= row_len)
		return (' ');
	return (game->map[y][x]);
}
