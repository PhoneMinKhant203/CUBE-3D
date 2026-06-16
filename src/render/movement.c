/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:17:06 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/16 15:09:41 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	rotate_player(t_game *game, double ang)
{
	double	pre_dir_x;
	double	pre_plane_x;

	pre_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(ang)
		- game->player.dir_y * sin(ang);
	game->player.dir_y = pre_dir_x * sin(ang)
		+ game->player.dir_y * cos(ang);
	pre_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(ang)
		- game->player.plane_y * sin(ang);
	game->player.plane_y = pre_plane_x * sin(ang)
		+ game->player.plane_y * cos(ang);
}

void	move_pos(t_game *game, double x, double y, double sp)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + (x * sp);
	new_y = game->player.y + (y * sp);
	if (!is_collision(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_collision(game, game->player.x, new_y))
		game->player.y = new_y;
}

static void	handle_movement(t_game *game, double m_speed, double ang)
{
	double	pos_x;
	double	pos_y;

	pos_x = game->player.dir_y;
	pos_y = game->player.dir_x;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_pos(game, pos_y, pos_x, m_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_pos(game, -pos_y, -pos_x, m_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_pos(game, pos_x, -pos_y, m_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_pos(game, -pos_x, pos_y, m_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, -ang);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, ang);
}

void	move_player(t_game *game)
{
	double	dt;
	double	m_speed;
	double	r_speed;

	dt = game->mlx->delta_time;
	if (game->mlx->delta_time > 0.05)
		dt = 0.05;
	m_speed = MOVE_SPEED * dt;
	r_speed = ROT_SPEED * dt;
	handle_movement(game, m_speed, r_speed);
	handle_mouse_toggle(game);
	handle_mouse_rotation(game);
	update_door(game);
}
