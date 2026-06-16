/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:02:47 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/06 16:13:13 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	get_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dx = (game->player.x - ray->map_x) * ray->delta_dx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dx = (ray->map_x + 1.0 - game->player.x) * ray->delta_dx;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dy = (game->player.y - ray->map_y) * ray->delta_dy;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dy = (ray->map_y + 1.0 - game->player.y) * ray->delta_dy;
	}
}

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	cam_x;

	cam_x = 2 * x / (double)G_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * cam_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * cam_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->hit = 0;
	if (ray->dir_x == 0)
		ray->delta_dx = 1e30;
	else
		ray->delta_dx = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dy = 1e30;
	else
		ray->delta_dy = fabs(1.0 / ray->dir_y);
	get_side_dist(game, ray);
}

static void	raycast_col(t_game *game, t_ray *ray, int x)
{
	init_ray(game, ray, x);
	while (1)
	{
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->delta_dx;
			ray->map_x += ray->step_x;
			ray->side = 'x';
		}
		else
		{
			ray->side_dy += ray->delta_dy;
			ray->map_y += ray->step_y;
			ray->side = 'y';
		}
		if (is_wall(game, ray->map_x, ray->map_y))
		{
			ray->hit = get_map_cell(game, ray->map_x, ray->map_y);
			break ;
		}
	}
}

void	raycast(t_game *game)
{
	t_ray	ray;
	size_t	x;

	x = 0;
	while (x < G_WIDTH)
	{
		raycast_col(game, &ray, x);
		draw_wall(game, &ray, x);
		game->z_buffer[x] = ray.perp_wall_dt;
		x++;
	}
}
