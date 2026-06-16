/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:00:13 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/05 11:57:14 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	handle_mouse_toggle(t_game *game)
{
	int	ispressed;

	ispressed = mlx_is_key_down(game->mlx, MLX_KEY_TAB);
	if (ispressed && !game->mouse_toggle)
	{
		if (game->mouse_lock)
		{
			game->mouse_lock = 0;
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		}
		else
		{
			game->mouse_lock = 1;
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
			mlx_set_mouse_pos(game->mlx, G_WIDTH / 2, G_HEIGHT / 2);
		}
	}
	game->mouse_toggle = ispressed;
}

void	handle_mouse_rotation(t_game *game)
{
	int32_t	center_x;
	int32_t	center_y;
	int32_t	mouse_x;
	int32_t	mouse_y;
	double	angle;

	if (!game->mouse_lock)
		return ;
	center_x = (int32_t)(G_WIDTH / 2.0);
	center_y = (int32_t)(G_HEIGHT / 2.0);
	mlx_get_mouse_pos(game->mlx, &mouse_x, &mouse_y);
	if (mouse_x == center_x && mouse_y == center_y)
		return ;
	angle = (mouse_x - center_x) * MOUSE_SENSITIVITY;
	if (angle > 0.25)
		angle = 0.25;
	else if (angle < -0.25)
		angle = -0.25;
	rotate_player(game, angle);
	mlx_set_mouse_pos(game->mlx, center_x, center_y);
}
