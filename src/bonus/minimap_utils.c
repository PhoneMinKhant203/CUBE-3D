/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 14:51:41 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/08 15:47:37 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	is_inside_map(int x, int y)
{
	int	right;
	int	bottom;

	right = MINI_MARGIN + (MINI_WIDTH * MINI_SCALE);
	bottom = MINI_MARGIN + (MINI_HEIGHT * MINI_SCALE);
	if (x < MINI_MARGIN || y < MINI_MARGIN)
		return (0);
	if (x >= right || y >= bottom)
		return (0);
	return (1);
}

void	put_pixel(t_game *game, int x, int y, uint32_t color)
{
	if (!is_inside_map(x, y))
		return ;
	if (x < 0 || y < 0)
		return ;
	if (x >= (int)G_WIDTH || y >= (int)G_HEIGHT)
		return ;
	mlx_put_pixel(game->tex.img, x, y, color);
}

void	draw_square(t_game *game, int x, int y, uint32_t color)
{
	int	i;
	int	j;
	int	w;
	int	h;

	i = 0;
	h = MINI_SCALE;
	w = MINI_SCALE;
	if (color == MINI_BG)
	{
		h = MINI_SCALE * MINI_HEIGHT;
		w = MINI_SCALE * MINI_WIDTH;
	}
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			put_pixel(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
